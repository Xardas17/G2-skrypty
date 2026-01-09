using System.Drawing;

namespace ParticleFxRenderer
{
    public sealed class Particle
    {
        public Vector3f Position;
        public Vector3f Velocity;
        public float Lifespan;
        public float Age;
        public Vector2f Size;
        public ColorF Color;
        public float Alpha;
        public Image Texture;

        public bool IsAlive => Age < Lifespan;

        public void Reset(Vector3f position, Vector3f velocity, float lifespan, Vector2f size, ColorF color, float alpha, Image texture)
        {
            Position = position;
            Velocity = velocity;
            Lifespan = lifespan;
            Age = 0f;
            Size = size;
            Color = color;
            Alpha = alpha;
            Texture = texture;
        }
    }
}
