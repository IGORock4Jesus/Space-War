using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SharpDX;
using Space_War_Managed.ECS;

namespace Space_War_Managed.UI
{
	class Collision : ECS.Component
	{
		public virtual bool Test(Vector2 point) { return false; }
	}

	class RectCollision : Collision
	{
		public RectangleF Rect { get; set; } = new RectangleF();

		public override bool Test(Vector2 point)
		{
			return point.X >= Rect.Left && point.X < Rect.Right
				&& point.Y >= Rect.Top && point.Y < Rect.Bottom;
		}
	}

	class CollisionSystem : ECS.System<Collision>
	{
		
	}
}
