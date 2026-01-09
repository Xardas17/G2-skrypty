using System;
using System.Drawing;
using System.Windows.Forms;

namespace ParticleFxRenderer
{
    public sealed class ParticleRenderControl : Control
    {
        private readonly Timer _timer;
        private DateTime _lastTick;

        public ParticleRenderControl()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.UserPaint, true);
            Camera = new Camera2D();
            _timer = new Timer { Interval = 16 };
            _timer.Tick += (_, __) => Tick();
        }

        public ParticleSystem ParticleSystem { get; set; }
        public Camera2D Camera { get; }

        public void Start()
        {
            _lastTick = DateTime.UtcNow;
            _timer.Start();
        }

        public void Stop()
        {
            _timer.Stop();
        }

        private void Tick()
        {
            var now = DateTime.UtcNow;
            var delta = (float)(now - _lastTick).TotalSeconds;
            _lastTick = now;

            if (ParticleSystem != null)
            {
                ParticleSystem.Update(delta);
            }

            Invalidate();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.Clear(Color.Black);
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            if (ParticleSystem != null)
            {
                var viewport = new Vector2f(Width, Height);
                ParticleSystem.Render(e.Graphics, Camera, viewport);
            }
        }
    }
}
