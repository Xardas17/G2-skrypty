using System;
using System.Drawing;

namespace ParticleFxRenderer
{
    public struct Vector2f
    {
        public float X;
        public float Y;

        public Vector2f(float x, float y)
        {
            X = x;
            Y = y;
        }

        public static Vector2f Zero => new Vector2f(0f, 0f);

        public float Length() => (float)Math.Sqrt(X * X + Y * Y);

        public Vector2f Normalized()
        {
            var len = Length();
            if (len <= 0.00001f)
            {
                return Zero;
            }

            return new Vector2f(X / len, Y / len);
        }

        public static Vector2f operator +(Vector2f a, Vector2f b) => new Vector2f(a.X + b.X, a.Y + b.Y);
        public static Vector2f operator -(Vector2f a, Vector2f b) => new Vector2f(a.X - b.X, a.Y - b.Y);
        public static Vector2f operator *(Vector2f a, float scalar) => new Vector2f(a.X * scalar, a.Y * scalar);
    }

    public struct Vector3f
    {
        public float X;
        public float Y;
        public float Z;

        public Vector3f(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public static Vector3f Zero => new Vector3f(0f, 0f, 0f);

        public float Length() => (float)Math.Sqrt(X * X + Y * Y + Z * Z);

        public Vector3f Normalized()
        {
            var len = Length();
            if (len <= 0.00001f)
            {
                return Zero;
            }

            return new Vector3f(X / len, Y / len, Z / len);
        }

        public static Vector3f operator +(Vector3f a, Vector3f b) => new Vector3f(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
        public static Vector3f operator -(Vector3f a, Vector3f b) => new Vector3f(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
        public static Vector3f operator *(Vector3f a, float scalar) => new Vector3f(a.X * scalar, a.Y * scalar, a.Z * scalar);
    }

    public struct ColorF
    {
        public float R;
        public float G;
        public float B;
        public float A;

        public ColorF(float r, float g, float b, float a = 1f)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }

        public static ColorF Lerp(ColorF from, ColorF to, float t)
        {
            t = Clamp01(t);
            return new ColorF(
                from.R + (to.R - from.R) * t,
                from.G + (to.G - from.G) * t,
                from.B + (to.B - from.B) * t,
                from.A + (to.A - from.A) * t);
        }

        public Color ToColor(float alphaMultiplier)
        {
            var alpha = Clamp01(A * alphaMultiplier);
            return Color.FromArgb(
                (int)(alpha * 255f),
                (int)(Clamp01(R) * 255f),
                (int)(Clamp01(G) * 255f),
                (int)(Clamp01(B) * 255f));
        }

        private static float Clamp01(float value)
        {
            if (value < 0f)
            {
                return 0f;
            }

            return value > 1f ? 1f : value;
        }
    }
}
