using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text.RegularExpressions;

namespace ParticleFxRenderer
{
    public sealed class DScriptParticleParser
    {
        private static readonly Regex InstanceRegex = new Regex(
            "Instance\\s+(?<name>\\w+)\\s*\\(C_PARTICLEFX\\)\\s*\\{(?<body>[^}]*)\\}",
            RegexOptions.IgnoreCase | RegexOptions.Multiline | RegexOptions.Singleline);

        public IReadOnlyList<ParticleEmitterDefinition> ParseInstances(string script)
        {
            if (string.IsNullOrWhiteSpace(script))
            {
                return Array.Empty<ParticleEmitterDefinition>();
            }

            var matches = InstanceRegex.Matches(script);
            var results = new List<ParticleEmitterDefinition>();
            foreach (Match match in matches)
            {
                var name = match.Groups["name"].Value;
                var body = match.Groups["body"].Value;
                var definition = ParseBody(name, body);
                results.Add(definition);
            }

            return results;
        }

        private static ParticleEmitterDefinition ParseBody(string name, string body)
        {
            var definition = new ParticleEmitterDefinition { Name = name };
            var statements = body.Split(new[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            foreach (var statement in statements)
            {
                var parts = statement.Split(new[] { '=' }, 2);
                if (parts.Length != 2)
                {
                    continue;
                }

                var key = parts[0].Trim().ToLowerInvariant();
                var rawValue = parts[1].Trim();
                var value = UnwrapQuotes(rawValue);

                ApplyValue(definition, key, value);
            }

            return definition;
        }

        private static void ApplyValue(ParticleEmitterDefinition definition, string key, string value)
        {
            switch (key)
            {
                case "ppsvalue":
                    definition.ParticlesPerSecond = ParseFloat(value, definition.ParticlesPerSecond);
                    break;
                case "ppsscalekeys_s":
                    ApplyFloatList(definition.ParticlesPerSecondScaleKeys, value);
                    break;
                case "ppsissmooth":
                    definition.ParticlesSmooth = ParseBool(value);
                    break;
                case "ppsislooping":
                    definition.ParticlesLooping = ParseBool(value);
                    break;
                case "ppsfps":
                    definition.ParticlesPerSecondFps = ParseFloat(value, definition.ParticlesPerSecondFps);
                    break;
                case "shptype_s":
                    definition.Shape = ParseShape(value);
                    break;
                case "shpfor_s":
                    definition.ShapeFor = ParseEmitterFor(value);
                    break;
                case "shpdistribtype_s":
                    definition.ShapeDistribution = ParseDistribution(value);
                    break;
                case "shpdim_s":
                    ApplyShapeDimensions(definition, value);
                    break;
                case "shpoffsetvec_s":
                    definition.ShapeOffset = ParseVector3(value, definition.ShapeOffset);
                    break;
                case "shpisvolume":
                    definition.ShapeIsVolume = ParseBool(value);
                    break;
                case "shpscalefps":
                    definition.ShapeScaleFps = ParseFloat(value, definition.ShapeScaleFps);
                    break;
                case "shpscalekeys_s":
                    ApplyFloatList(definition.ShapeScaleKeys, value);
                    break;
                case "shpscaleislooping":
                    definition.ShapeScaleLooping = ParseBool(value);
                    break;
                case "shpscaleissmooth":
                    definition.ShapeScaleSmooth = ParseBool(value);
                    break;
                case "dirfor_s":
                    definition.DirectionFor = ParseEmitterFor(value);
                    break;
                case "dirmodetargetfor_s":
                    definition.DirectionTargetFor = ParseEmitterFor(value);
                    break;
                case "dirmodetargetpos_s":
                    definition.DirectionTargetPosition = ParseVector3(value, definition.DirectionTargetPosition);
                    break;
                case "diranglehead":
                    definition.DirectionAngleHead = ParseFloat(value, definition.DirectionAngleHead);
                    break;
                case "dirangleheadvar":
                    definition.DirectionAngleHeadVariance = ParseFloat(value, definition.DirectionAngleHeadVariance);
                    break;
                case "dirangleelev":
                    definition.DirectionAngleElev = ParseFloat(value, definition.DirectionAngleElev);
                    break;
                case "dirangleelevvar":
                    definition.DirectionAngleElevVariance = ParseFloat(value, definition.DirectionAngleElevVariance);
                    break;
                case "velavg":
                    definition.VelocityAverage = ParseFloat(value, definition.VelocityAverage);
                    break;
                case "velvar":
                    definition.VelocityVariance = ParseFloat(value, definition.VelocityVariance);
                    break;
                case "lsppartavg":
                    definition.LifespanAverage = ParseMillisecondsToSeconds(value, definition.LifespanAverage);
                    break;
                case "lsppartvar":
                    definition.LifespanVariance = ParseMillisecondsToSeconds(value, definition.LifespanVariance);
                    break;
                case "flygravity_s":
                    definition.Gravity = ParseVector3(value, definition.Gravity);
                    break;
                case "visname_s":
                    definition.TexturePath = value;
                    break;
                case "vistexisquadpoly":
                    definition.TextureIsQuad = ParseBool(value);
                    break;
                case "vistexanifps":
                    definition.TextureAnimFps = ParseFloat(value, definition.TextureAnimFps);
                    break;
                case "vistexaniislooping":
                    definition.TextureAnimLooping = ParseLoop(value);
                    break;
                case "vistexcolorstart_s":
                    definition.ColorStart = ParseColor(value, definition.ColorStart);
                    break;
                case "vistexcolorend_s":
                    definition.ColorEnd = ParseColor(value, definition.ColorEnd);
                    break;
                case "vissizestart_s":
                    definition.SizeStart = ParseVector2(value, definition.SizeStart);
                    break;
                case "vissizeendscale":
                    definition.SizeEndScale = ParseFloat(value, definition.SizeEndScale);
                    break;
                case "visalphafunc_s":
                    definition.AlphaBlendFunc = ParseAlphaFunc(value);
                    break;
                case "visalphastart":
                    definition.AlphaStart = ParseByteToUnit(value, definition.AlphaStart);
                    break;
                case "visalphaend":
                    definition.AlphaEnd = ParseByteToUnit(value, definition.AlphaEnd);
                    break;
                case "dirmode_s":
                    definition.DirectionMode = ParseDirectionMode(value);
                    break;
            }
        }

        private static string UnwrapQuotes(string value)
        {
            value = value.Trim();
            if (value.StartsWith("\"") && value.EndsWith("\""))
            {
                return value.Substring(1, value.Length - 2);
            }

            return value;
        }

        private static float ParseFloat(string value, float fallback)
        {
            if (float.TryParse(value, NumberStyles.Float, CultureInfo.InvariantCulture, out var parsed))
            {
                return parsed;
            }

            return fallback;
        }

        private static float ParseMillisecondsToSeconds(string value, float fallback)
        {
            var ms = ParseFloat(value, fallback * 1000f);
            return ms / 1000f;
        }

        private static bool ParseBool(string value)
        {
            if (int.TryParse(value, NumberStyles.Integer, CultureInfo.InvariantCulture, out var i))
            {
                return i != 0;
            }

            return value.Equals("true", StringComparison.OrdinalIgnoreCase);
        }

        private static bool ParseLoop(string value)
        {
            if (int.TryParse(value, NumberStyles.Integer, CultureInfo.InvariantCulture, out var i))
            {
                return i != 0;
            }

            return ParseBool(value);
        }

        private static Vector3f ParseVector3(string value, Vector3f fallback)
        {
            var parts = value.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            if (parts.Length < 3)
            {
                return fallback;
            }

            return new Vector3f(
                ParseFloat(parts[0], fallback.X),
                ParseFloat(parts[1], fallback.Y),
                ParseFloat(parts[2], fallback.Z));
        }

        private static Vector2f ParseVector2(string value, Vector2f fallback)
        {
            var parts = value.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            if (parts.Length < 2)
            {
                return fallback;
            }

            return new Vector2f(
                ParseFloat(parts[0], fallback.X),
                ParseFloat(parts[1], fallback.Y));
        }

        private static void ApplyShapeDimensions(ParticleEmitterDefinition definition, string value)
        {
            var parts = value.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            if (parts.Length == 1)
            {
                var radius = ParseFloat(parts[0], definition.ShapeRadius);
                definition.ShapeRadius = radius;
                definition.ShapeDimensions = new Vector3f(radius, radius, radius);
                return;
            }

            if (parts.Length >= 3)
            {
                definition.ShapeDimensions = ParseVector3(value, definition.ShapeDimensions);
            }
        }

        private static void ApplyFloatList(ICollection<float> target, string value)
        {
            if (target == null)
            {
                return;
            }

            target.Clear();
            var parts = value.Split(new[] { ' ', ',', '\t' }, StringSplitOptions.RemoveEmptyEntries);
            foreach (var part in parts)
            {
                if (float.TryParse(part, NumberStyles.Float, CultureInfo.InvariantCulture, out var parsed))
                {
                    target.Add(parsed);
                }
            }
        }

        private static ColorF ParseColor(string value, ColorF fallback)
        {
            var parts = value.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            if (parts.Length < 3)
            {
                return fallback;
            }

            return new ColorF(
                ParseByteToUnit(parts[0], fallback.R),
                ParseByteToUnit(parts[1], fallback.G),
                ParseByteToUnit(parts[2], fallback.B),
                fallback.A);
        }

        private static float ParseByteToUnit(string value, float fallback)
        {
            if (float.TryParse(value, NumberStyles.Float, CultureInfo.InvariantCulture, out var parsed))
            {
                if (parsed > 1f)
                {
                    return parsed / 255f;
                }

                return parsed;
            }

            return fallback;
        }

        private static EmitterShape ParseShape(string value)
        {
            switch (value.Trim().ToLowerInvariant())
            {
                case "line":
                    return EmitterShape.Line;
                case "box":
                    return EmitterShape.Box;
                case "circle":
                    return EmitterShape.Circle;
                case "sphere":
                    return EmitterShape.Sphere;
                case "mesh":
                    return EmitterShape.Mesh;
                default:
                    return EmitterShape.Point;
            }
        }

        private static EmitterFor ParseEmitterFor(string value)
        {
            switch (value.Trim().ToLowerInvariant())
            {
                case "object":
                    return EmitterFor.Object;
                case "object_each_frame":
                    return EmitterFor.ObjectEachFrame;
                default:
                    return EmitterFor.World;
            }
        }

        private static DistributionType ParseDistribution(string value)
        {
            switch (value.Trim().ToLowerInvariant())
            {
                case "uniform":
                    return DistributionType.Uniform;
                case "walk":
                    return DistributionType.Walk;
                default:
                    return DistributionType.Random;
            }
        }

        private static AlphaFunc ParseAlphaFunc(string value)
        {
            switch (value.Trim().ToLowerInvariant())
            {
                case "add":
                    return AlphaFunc.Add;
                case "mul":
                case "multiply":
                    return AlphaFunc.Multiply;
                default:
                    return AlphaFunc.Blend;
            }
        }

        private static DirectionMode ParseDirectionMode(string value)
        {
            switch (value.Trim().ToLowerInvariant())
            {
                case "target":
                    return DirectionMode.Target;
                case "mesh":
                    return DirectionMode.Mesh;
                case "none":
                    return DirectionMode.None;
                default:
                    return DirectionMode.Direction;
            }
        }
    }
}
