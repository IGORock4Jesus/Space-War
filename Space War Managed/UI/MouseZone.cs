using SharpDX;
using Space_War_Managed.ECS;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Space_War_Managed.UI
{
	class MouseZone : Component
	{
		/// <summary>
		/// Находится ли курсор мыши внутри зоны.
		/// </summary>
		public bool IsMouseOver { get; private set; }
		Collision collision;

		public delegate void PointHandler(Entity entity, Vector2 point);
		public delegate void PointWheelHandler(Entity entity, Vector2 point, int wheel);
		public event PointHandler Enter, Leave;
		public event PointHandler Move, Down, Up;
		public event PointWheelHandler Wheel;


		protected override void OnInitialize(Entity entity)
		{
			collision = entity.Get<Collision>();
		}

		internal bool Test(Vector2 point)
		{
			return IsMouseOver = collision.Test(point);
		}

		internal void DoDown(Vector2 point)
		{
			Down?.Invoke(Entity, point);
		}

		internal void DoUp(Vector2 point)
		{
			Up?.Invoke(Entity, point);
		}

		internal void DoEnter(Vector2 point)
		{
			Enter?.Invoke(Entity, point);
		}

		internal void DoLeave(Vector2 point)
		{
			Leave?.Invoke(Entity, point);
			IsMouseOver = false;
		}

		internal void DoWheel(Vector2 point, int wheel)
		{
			Wheel?.Invoke(Entity, point, wheel);
		}

		internal void DoMove(Vector2 point)
		{
			Move?.Invoke(Entity, point);
		}
	}


	class MouseZoneSystem : System<MouseZone>
	{
		public MouseZoneSystem(Input input)
		{
			input.MouseDown += Form_MouseDown;
			input.MouseUp += Form_MouseUp;
			input.MouseMove += Form_MouseMove;
			input.MouseWheel += Form_MouseWheel;
		}

		private void Form_MouseDown(Input.Mouse mouse)
		{
			var point = new Vector2(mouse.Cursor.X, mouse.Cursor.Y);
			foreach (var c in Components)
			{
				if (c.Test(point))
				{
					c.DoDown(point);
				}
			}
		}

		private void Form_MouseUp(Input.Mouse mouse)
		{
			var point = new Vector2(mouse.Cursor.X, mouse.Cursor.Y);
			foreach (var c in Components)
			{
				if (c.Test(point))
				{
					c.DoUp(point);
				}
			}
		}

		private void Form_MouseMove(Input.Mouse mouse)
		{
			var point = new Vector2(mouse.Cursor.X, mouse.Cursor.Y);
			foreach (var c in Components)
			{
				var isOver = c.IsMouseOver;
				var newValue = c.Test(point);
				if (isOver != newValue)
				{
					if (newValue)
						c.DoEnter(point);
					else
						c.DoLeave(point);
				}
				else if(isOver && newValue)
				{
					c.DoMove(point);
				}
			}
		}

		private void Form_MouseWheel(Input.Mouse mouse)
		{
			var point = new Vector2(mouse.Cursor.X, mouse.Cursor.Y);
			int wheel = mouse.Wheel;
			foreach (var c in Components)
			{
				if (c.Test(point))
				{
					c.DoWheel(point,wheel);
				}
			}
		}
	}
}
