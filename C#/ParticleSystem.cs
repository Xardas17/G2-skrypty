using System;
using System.Collections.Generic;
using System.Drawing;

namespace ParticleFxRenderer
{
    public sealed class ParticleSystem
    {
        private readonly List<Particle> _particles = new List<Particle>();
        private readonly Random _random = new Random();
        private float _spawnAccumulator;
        private float _elapsed;

        public ParticleSystem(ParticleEmitterDefinition definition)
        {
            Definition = definition;
        }

        public ParticleEmitterDefinition Definition { get; }
        public IReadOnlyList<Particle> Particles => _particles;
        public Image Texture { get; private set; }
        public bool IsEmitting { get; set; } = true;

        public void SetTexture(Image texture)
        {
            Texture = texture;
        }

        public void Update(float deltaSeconds)
        {
            if (deltaSeconds <= 0f)
            {
                return;
            }

            _elapsed += deltaSeconds;

            EmitParticles(deltaSeconds);
            UpdateParticles(deltaSeconds);
        }

        private void EmitParticles(float deltaSeconds)
        {
            if (!IsEmitting)
            {
                return;
            }

            if (!Definition.ParticlesLooping && Definition.EndTime > 0f && _elapsed > Definition.EndTime)
            {
                return;
            }

            var pps = Math.Max(0f, Definition.ParticlesPerSecond);
            _spawnAccumulator += pps * deltaSeconds;
            var spawnCount = (int)_spawnAccumulator;
            if (spawnCount <= 0)
            {
                return;
            }

            _spawnAccumulator -= spawnCount;
            for (var i = 0; i < spawnCount; i++)
            {
                SpawnParticle();
            }
        }

        private void SpawnParticle()
        {
            var lifespan = Definition.LifespanAverage + NextVariance(Definition.LifespanVariance);
            if (lifespan <= 0f)
            {
                lifespan = 0.1f;
            }

            var position = CreatePosition();
            var velocity = CreateVelocity();
            var size = Definition.SizeStart;
            var color = Definition.ColorStart;
            var alpha = Definition.AlphaStart;
            var particle = new Particle();
            particle.Reset(position, velocity, lifespan, size, color, alpha, Texture);
            _particles.Add(particle);
        }

        private Vector3f CreatePosition()
        {
            switch (Definition.Shape)
            {
                case EmitterShape.Line:
                    return Definition.ShapeOffset + RandomLine();
                case EmitterShape.Box:
                    return Definition.ShapeOffset + RandomBox();
                case EmitterShape.Circle:
                    return Definition.ShapeOffset + RandomCircle();
                case EmitterShape.Sphere:
                    return Definition.ShapeOffset + RandomSphere();
                case EmitterShape.Point:
                default:
                    return Definition.ShapeOffset;
            }
        }

        private Vector3f RandomLine()
        {
            var dim = Definition.ShapeDimensions;
            var t = Next01();
            return new Vector3f(dim.X * (t - 0.5f), dim.Y * (t - 0.5f), dim.Z * (t - 0.5f));
        }

        private Vector3f RandomBox()
        {
            var dim = Definition.ShapeDimensions;
            if (Definition.ShapeIsVolume)
            {
                return new Vector3f(
                    (Next01() - 0.5f) * dim.X,
                    (Next01() - 0.5f) * dim.Y,
                    (Next01() - 0.5f) * dim.Z);
            }

            var face = _random.Next(0, 6);
            var x = (Next01() - 0.5f) * dim.X;
            var y = (Next01() - 0.5f) * dim.Y;
            var z = (Next01() - 0.5f) * dim.Z;
            switch (face)
            {
                case 0: x = -0.5f * dim.X; break;
                case 1: x = 0.5f * dim.X; break;
                case 2: y = -0.5f * dim.Y; break;
                case 3: y = 0.5f * dim.Y; break;
                case 4: z = -0.5f * dim.Z; break;
                default: z = 0.5f * dim.Z; break;
            }

            return new Vector3f(x, y, z);
        }

        private Vector3f RandomCircle()
        {
            var angle = Next01() * (float)Math.PI * 2f;
            var radius = Definition.ShapeRadius * (float)Math.Sqrt(Next01());
            return new Vector3f(
                (float)Math.Cos(angle) * radius,
                (float)Math.Sin(angle) * radius,
                0f);
        }

        private Vector3f RandomSphere()
        {
            var u = Next01();
            var v = Next01();
            var theta = 2f * (float)Math.PI * u;
            var phi = (float)Math.Acos(2f * v - 1f);
            var radius = Definition.ShapeRadius * (float)Math.Cbrt(Next01());
            return new Vector3f(
                radius * (float)(Math.Sin(phi) * Math.Cos(theta)),
                radius * (float)(Math.Sin(phi) * Math.Sin(theta)),
                radius * (float)Math.Cos(phi));
        }

        private Vector3f CreateVelocity()
        {
            var direction = CreateDirection();
            var speed = Definition.VelocityAverage + NextVariance(Definition.VelocityVariance);
            return direction * speed;
        }

        private Vector3f CreateDirection()
        {
            if (Definition.DirectionMode == DirectionMode.Target)
            {
                return Definition.DirectionTargetPosition.Normalized();
            }

            if (Definition.DirectionMode == DirectionMode.None)
            {
                return new Vector3f(0f, 1f, 0f);
            }

            var head = DegreesToRadians(Definition.DirectionAngleHead + NextVariance(Definition.DirectionAngleHeadVariance));
            var elev = DegreesToRadians(Definition.DirectionAngleElev + NextVariance(Definition.DirectionAngleElevVariance));
            var x = (float)(Math.Cos(elev) * Math.Cos(head));
            var y = (float)Math.Sin(elev);
            var z = (float)(Math.Cos(elev) * Math.Sin(head));
            return new Vector3f(x, y, z).Normalized();
        }

        private void UpdateParticles(float deltaSeconds)
        {
            for (var i = _particles.Count - 1; i >= 0; i--)
            {
                var particle = _particles[i];
                particle.Age += deltaSeconds;

                if (!particle.IsAlive)
                {
                    _particles.RemoveAt(i);
                    continue;
                }

                particle.Velocity += Definition.Gravity * deltaSeconds;
                particle.Position += particle.Velocity * deltaSeconds;

                var t = particle.Age / particle.Lifespan;
                var sizeScale = 1f + (Definition.SizeEndScale - 1f) * t;
                particle.Size = Definition.SizeStart * sizeScale;
                particle.Color = ColorF.Lerp(Definition.ColorStart, Definition.ColorEnd, t);
                particle.Alpha = Definition.AlphaStart + (Definition.AlphaEnd - Definition.AlphaStart) * t;
            }
        }

        public void Render(Graphics graphics, Camera2D camera, Vector2f viewport)
        {
            foreach (var particle in _particles)
            {
                RenderParticle(graphics, camera, viewport, particle);
            }
        }

        private void RenderParticle(Graphics graphics, Camera2D camera, Vector2f viewport, Particle particle)
        {
            var screen = camera.WorldToScreen(new Vector2f(particle.Position.X, particle.Position.Y), viewport);
            var width = particle.Size.X;
            var height = particle.Size.Y;
            var rect = new RectangleF(screen.X - width * 0.5f, screen.Y - height * 0.5f, width, height);
            var color = particle.Color.ToColor(particle.Alpha);

            if (particle.Texture != null)
            {
                using (var attributes = new System.Drawing.Imaging.ImageAttributes())
                {
                    var matrix = new float[][]
                    {
                        new float[] { 1f, 0f, 0f, 0f, 0f },
                        new float[] { 0f, 1f, 0f, 0f, 0f },
                        new float[] { 0f, 0f, 1f, 0f, 0f },
                        new float[] { 0f, 0f, 0f, color.A / 255f, 0f },
                        new float[] { 0f, 0f, 0f, 0f, 1f }
                    };
                    var cm = new System.Drawing.Imaging.ColorMatrix(matrix);
                    attributes.SetColorMatrix(cm);
                    graphics.DrawImage(
                        particle.Texture,
                        Rectangle.Round(rect),
                        0,
                        0,
                        particle.Texture.Width,
                        particle.Texture.Height,
                        GraphicsUnit.Pixel,
                        attributes);
                }
            }
            else
            {
                using (var brush = new SolidBrush(color))
                {
                    graphics.FillEllipse(brush, rect);
                }
            }
        }

        private float Next01() => (float)_random.NextDouble();

        private float NextVariance(float variance) => (Next01() * 2f - 1f) * variance;

        private static float DegreesToRadians(float degrees) => degrees * (float)Math.PI / 180f;
    }
}
