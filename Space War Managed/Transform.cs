using SharpDX;
using Space_War_Managed.ECS;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed
{
	class Transform : Component
	{
		public Vector2 Postion { get; set; } = new Vector2(0.0f);
		public Vector2 Scaling { get; set; } = new Vector2(1.0f);
		public float Rotation { get; set; }
	}

	class TransformSystem : System<Transform>
	{

	}
}
