using System.Collections.Generic;

namespace ParticleFxRenderer
{
    public enum EmitterShape
    {
        Point,
        Line,
        Box,
        Circle,
        Sphere,
        Mesh
    }

    public enum EmitterFor
    {
        World,
        Object,
        ObjectEachFrame
    }

    public enum DirectionMode
    {
        None,
        Direction,
        Target,
        Mesh
    }

    public enum VisualOrientation
    {
        None,
        VelocityAligned,
        VobXZPlane,
        VelocityAligned3D
    }

    public enum DistributionType
    {
        Random,
        Uniform,
        Walk
    }

    public enum FlockMode
    {
        None,
        Wind,
        WindPlants
    }

    public enum AlphaFunc
    {
        Blend,
        Add,
        Multiply
    }

    public sealed class ParticleEmitterDefinition
    {
        public string Name { get; set; }

        // 1) Emission
        public float ParticlesPerSecond { get; set; } = 10f;
        public List<float> ParticlesPerSecondScaleKeys { get; } = new List<float>();
        public bool ParticlesLooping { get; set; } = true;
        public bool ParticlesSmooth { get; set; } = true;
        public float ParticlesPerSecondFps { get; set; } = 25f;
        public float CreateEmitterDelay { get; set; }

        // 2) Shape
        public EmitterShape Shape { get; set; } = EmitterShape.Point;
        public EmitterFor ShapeFor { get; set; } = EmitterFor.World;
        public Vector3f ShapeOffset { get; set; } = Vector3f.Zero;
        public DistributionType ShapeDistribution { get; set; } = DistributionType.Random;
        public float ShapeDistributionWalkSpeed { get; set; } = 1f;
        public bool ShapeIsVolume { get; set; } = true;
        public Vector3f ShapeDimensions { get; set; } = new Vector3f(10f, 10f, 10f);
        public float ShapeRadius { get; set; } = 10f;
        public bool ShapeMeshRender { get; set; }
        public List<float> ShapeScaleKeys { get; } = new List<float>();
        public bool ShapeScaleLooping { get; set; } = true;
        public bool ShapeScaleSmooth { get; set; } = true;
        public float ShapeScaleFps { get; set; } = 25f;

        // 3) Direction + velocity
        public DirectionMode DirectionMode { get; set; } = DirectionMode.Direction;
        public EmitterFor DirectionFor { get; set; } = EmitterFor.World;
        public EmitterFor DirectionTargetFor { get; set; } = EmitterFor.World;
        public Vector3f DirectionTargetPosition { get; set; } = new Vector3f(0f, 1f, 0f);
        public float DirectionAngleHead { get; set; } = 0f;
        public float DirectionAngleHeadVariance { get; set; } = 180f;
        public float DirectionAngleElev { get; set; } = 0f;
        public float DirectionAngleElevVariance { get; set; } = 45f;
        public float VelocityAverage { get; set; } = 30f;
        public float VelocityVariance { get; set; } = 10f;

        // 4) Lifespan
        public float LifespanAverage { get; set; } = 1.5f;
        public float LifespanVariance { get; set; } = 0.5f;

        // 5) Flight
        public Vector3f Gravity { get; set; } = new Vector3f(0f, 0f, 0f);
        public bool CollisionDetection { get; set; }

        // 6) Visuals
        public string TexturePath { get; set; }
        public VisualOrientation Orientation { get; set; } = VisualOrientation.VelocityAligned;
        public bool TextureIsQuad { get; set; } = true;
        public float TextureAnimFps { get; set; }
        public bool TextureAnimLooping { get; set; } = true;
        public ColorF ColorStart { get; set; } = new ColorF(1f, 1f, 1f, 1f);
        public ColorF ColorEnd { get; set; } = new ColorF(1f, 1f, 1f, 0f);
        public Vector2f SizeStart { get; set; } = new Vector2f(10f, 10f);
        public float SizeEndScale { get; set; } = 0.2f;
        public AlphaFunc AlphaBlendFunc { get; set; } = AlphaFunc.Blend;
        public float AlphaStart { get; set; } = 1f;
        public float AlphaEnd { get; set; } = 0f;

        // 7) Trails/marks
        public float TrailFadeSpeed { get; set; }
        public string TrailTexturePath { get; set; }
        public float TrailWidth { get; set; }

        public float MarkFadeSpeed { get; set; }
        public string MarkTexturePath { get; set; }
        public float MarkSize { get; set; }

        // 8) Flocking/ambient
        public FlockMode Flocking { get; set; } = FlockMode.None;
        public float FlockWeight { get; set; }
        public bool SlowLocalFor { get; set; }
        public float StartTime { get; set; }
        public float EndTime { get; set; }
        public bool IsAmbient { get; set; }
    }
}