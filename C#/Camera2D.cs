namespace ParticleFxRenderer
{
    public sealed class Camera2D
    {
        public Vector2f Position { get; set; } = Vector2f.Zero;
        public float Zoom { get; set; } = 1f;

        public Vector2f WorldToScreen(Vector2f world, Vector2f viewportSize)
        {
            var centered = world - Position;
            return new Vector2f(
                viewportSize.X * 0.5f + centered.X * Zoom,
                viewportSize.Y * 0.5f - centered.Y * Zoom);
        }
    }
}
