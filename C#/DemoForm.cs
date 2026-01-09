using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace ParticleFxRenderer
{
    public sealed class DemoForm : Form
    {
        private readonly ParticleRenderControl _renderControl;

        public DemoForm()
        {
            Text = "Particle FX Renderer (Gothic-style)";
            Width = 1024;
            Height = 768;

            _renderControl = new ParticleRenderControl { Dock = DockStyle.Fill };
            Controls.Add(_renderControl);

            var parser = new DScriptParticleParser();
            var script = @"Instance armorcricket_acid (C_PARTICLEFX)
{
     ppsvalue = 12;
     ppsscalekeys_s = ""1 "";
     ppsissmooth = 1;
     ppsfps = 2;
     shptype_s = ""sphere"";
     shpfor_s = ""Object"";
     shpdistribtype_s = ""Rand"";
     shpdim_s = ""10"";
     shpoffsetvec_s = ""0 0 0"";
     shpisvolume = 1;
     shpscalekeys_s = ""1"";
     shpscaleislooping = 1;
     shpscaleissmooth = 1;
     shpscalefps = 2;
     dirfor_s = ""object"";
     dirmodetargetfor_s = ""object"";
     dirmodetargetpos_s = ""0 0 0"";
     diranglehead = 180;
     dirangleheadvar = 180;
     dirangleelev = -90;
     velavg = 0.001;
     lsppartavg = 4000;
     lsppartvar = 1000;
     flygravity_s = ""0 -0.0000001 0"";
     visname_s = ""mfx_magiccloud.TGA"";
     vistexisquadpoly = 1;
     vistexanifps = 18;
     vistexaniislooping = 2;
     vistexcolorstart_s = ""0 255 0"";
     vistexcolorend_s = ""200 200 200"";
     vissizestart_s = ""50 50"";
     vissizeendscale = 2;
     visalphafunc_s = ""add"";
     visalphastart = 255;
};";

            var parsed = parser.ParseInstances(script);
            var definition = parsed.Count > 0 ? parsed[0] : new ParticleEmitterDefinition { Name = "DemoEmitter" };

            var system = new ParticleSystem(definition);
            TryLoadTexture(definition, system);
            _renderControl.ParticleSystem = system;
        }

        protected override void OnShown(System.EventArgs e)
        {
            base.OnShown(e);
            _renderControl.Start();
        }

        private static void TryLoadTexture(ParticleEmitterDefinition definition, ParticleSystem system)
        {
            if (string.IsNullOrWhiteSpace(definition.TexturePath))
            {
                return;
            }

            var path = definition.TexturePath;
            if (!File.Exists(path))
            {
                return;
            }

            system.SetTexture(Image.FromFile(path));
        }
    }
}
