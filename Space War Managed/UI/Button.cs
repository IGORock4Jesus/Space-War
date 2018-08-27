using SharpDX;
using Space_War_Managed.ECS;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed.UI
{
	class Button : Component
	{
		MouseZone mouseZone;
		private Sprite sprite;
		bool isPressed;
		private Label label;

		public bool IsPressed => isPressed;

		protected override void OnInitialize(Entity entity)
		{
			mouseZone = entity.Get<MouseZone>();
			mouseZone.Enter += MouseZone_Enter;
			mouseZone.Leave += MouseZone_Leave;
			mouseZone.Down += MouseZone_Down;
			mouseZone.Up += MouseZone_Up;

			sprite = entity.Get<Sprite>();
			sprite.Color = Color.Green;

			label = entity.Get<Label>();
			label.Color = Color.White;
		}

		private void MouseZone_Up(Entity entity, Vector2 point)
		{
			if (isPressed)
			{
				isPressed = false;
				Click?.Invoke(Entity);
			}
		}

		private void MouseZone_Down(Entity entity, Vector2 point)
		{
			isPressed = true;
		}

		public delegate void EntityHandler(Entity entity);
		public event EntityHandler Click;

		private void MouseZone_Leave(Entity entity, SharpDX.Vector2 point)
		{
			sprite.Color = Color.Green;
			label.Color = Color.White;
		}

		private void MouseZone_Enter(Entity entity, SharpDX.Vector2 point)
		{
			sprite.Color = Color.Yellow;
			label.Color = Color.Red;
		}
	}

	class ButtonSystem : System<Button>
	{

	}
}
