using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SharpDX;
using SharpDX.Direct3D9;
using Space_War_Managed.ECS;

namespace Space_War_Managed.UI
{
	class Label : ECS.Component, IDisposable
	{
		public Transform Transform { get; private set; }
		public string Text { get; set; } = "Label";
		public int FontSize { get; set; } = 16;
		public Color Color { get; set; } = Color.White;
		//public Font Font { get; private set; }

		protected override void OnInitialize(Entity entity)
		{
			Transform = entity.Get<Transform>();
		}

		protected override void OnInitialArguments(params object[] ps)
		{
			if (!(ps[0] is Renderer renderer)) return;

			//Font = new Font(renderer.Device, FontSize, 0, FontWeight.Normal, 0, false, FontCharacterSet.Russian, FontPrecision.TrueType, FontQuality.ClearType, FontPitchAndFamily.Roman, "Consolas");
		}

		public void Dispose()
		{
			//if (Font != null)
			//	Font.Dispose();
		}
	}

	class LabelSystem : ECS.System<Label>
	{
		private readonly Renderer renderer;
		Dictionary<FontDescription, Graphics.Font> fonts = new Dictionary<FontDescription, Graphics.Font>();


		public LabelSystem(Renderer renderer)
		{
			this.renderer = renderer;
		}

		public override Label Create(Entity entity, params object[] ps)
		{
			return base.Create(entity, renderer);
		}

		internal override void Render(Renderer renderer)
		{
			var device = renderer.Device;
			foreach (var c in Components)
			{
				//using (var font = new Font(device, c.FontSize, 0, FontWeight.Normal, 0, false, FontCharacterSet.Russian, FontPrecision.TrueType, FontQuality.ClearType, FontPitchAndFamily.Roman, "Consolas"))
				//{
				//	font.DrawText(null, c.Text, (int)c.Transform.Postion.X, (int)c.Transform.Postion.Y, c.Color);
				//}

				FontDescription description = new FontDescription
				{
					CharacterSet = FontCharacterSet.Russian,
					FaceName = "Consolas",
					Height = c.FontSize,
					Italic = false,
					MipLevels = 0,
					OutputPrecision = FontPrecision.TrueType,
					PitchAndFamily = FontPitchAndFamily.Roman,
					Quality = FontQuality.ClearType,
					Weight = FontWeight.Normal,
					Width = 0
				};


				if (!fonts.TryGetValue(description, out Graphics.Font font))
				{
					font = new Graphics.Font(renderer, description);
					fonts.Add(description, font);
				}

				var s = c.Entity.Get<Sprite>().Size;

				font?.DrawText(c.Text, new Rectangle((int)c.Transform.Postion.X, (int)c.Transform.Postion.Y, (int)s.Width, (int)s.Height), FontDrawFlags.Center | FontDrawFlags.VerticalCenter, c.Color);

			}
		}
	}
}
