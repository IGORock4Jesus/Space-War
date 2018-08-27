using SharpDX;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed.UI
{
	class Manager
	{
		ECS.Manager ecs;
		ECS.Scene scene;

		public Manager(ECS.Manager ecs, ECS.Scene scene)
		{
			this.ecs = ecs;
			this.scene = scene;
		}

		public ECS.Entity CreateButton(Vector2 position, Size2F size, string text)
		{
			ECS.Entity entity = new ECS.Entity();
			var transform = ecs.Get<TransformSystem>().Create(entity);
			transform.Postion = position;

			var collider = new UI.RectCollision
			{
				Rect = new RectangleF { Location = position, Size = size }
			};
			ecs.Get<CollisionSystem>().Add(entity, collider);

			var sprite = ecs.Get<SpriteSystem>().Create(entity);
			sprite.Size = size;
			sprite.Color = Color.Green;

			var mouseZone = ecs.Get<MouseZoneSystem>().Create(entity);

			var label = ecs.Get<LabelSystem>().Create(entity);
			label.Text = text;

			var button = ecs.Get<ButtonSystem>().Create(entity);

			return entity;
		}
	}
}
