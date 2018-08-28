using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SharpDX;
using Space_War_Managed.ECS;

namespace Space_War_Managed
{
	class GalaxyConstructor : GameStackItem
	{
		enum Tools
		{
			Select, Planet, Ship
		}

		Tools currentTool = Tools.Select;

		public override void Initialize()
		{
			Input.KeyDown += Input_KeyDown;

			InitializeControls();
		}

		private void InitializeControls()
		{
			var createPanel = UI.CreatePanel(new Vector2(1, 1), new Size2F(140 - 2, MainForm.ClientSize.Height - 2), Color.LightGray);
			Scene.Add(createPanel);

			var planetButton = UI.CreateButton(new Vector2(20, 20), new Size2F(100, 100), "Планета");
			planetButton.Get<UI.Button>().Click += PlanetButton_Click;
			Scene.Add(planetButton);

			var shipButton = UI.CreateButton(new Vector2(20, 140), new Size2F(100, 100), "Корабль");
			shipButton.Get<UI.Button>().Click += ShipButton_Click;
			Scene.Add(shipButton);

			var constructorField = UI.CreateGalaxyConstructor(new Vector2(144, 1), new Size2F(MainForm.ClientSize.Width - 144 - 1, MainForm.ClientSize.Height - 2));
			Scene.Add(constructorField);
			var mz = constructorField.Get<UI.MouseZone>();
			mz.Down += ConstructorField_MouseDown;

		}

		private void ConstructorField_MouseDown(Entity entity, Vector2 point)
		{
			switch (currentTool)
			{
				case Tools.Select:
					break;
				case Tools.Planet:
					CreatePlanet(point);
					break;
				case Tools.Ship:
					break;
				default:
					break;
			}
		}

		private void CreatePlanet(Vector2 point)
		{
			ECS.Entity entity = new Entity();
			var transform = ECS.Get<TransformSystem>().Create(entity);
			transform.Postion = point;
			var image = ECS.Get<ImageSystem>().Create(entity);
			image.Texture = ECS.Get<ImageSystem>().LoadFile(@"C:\Users\IGORo\Pictures\Positive.png");
			image.Size = new Size2F(100, 100);
			Scene.Add(entity);
		}

		private void ShipButton_Click(Entity entity)
		{
			currentTool = Tools.Ship;
		}

		private void PlanetButton_Click(Entity entity)
		{
			currentTool = Tools.Planet;
		}

		public override void Release()
		{
			Input.KeyDown -= Input_KeyDown;
		}

		private void Input_KeyDown(System.Windows.Forms.Keys key)
		{
			if (key == System.Windows.Forms.Keys.Escape)
			{
				if (currentTool == Tools.Select)
					GameStack.Pop();
				else
				{
					currentTool = Tools.Select;
				}
			}
		}
	}
}
