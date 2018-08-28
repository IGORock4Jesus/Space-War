using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed.ECS
{
	class Scene
	{
		readonly List<Entity> entities = new List<Entity>();

		public Entity Find(string name)
		{
			return entities.FirstOrDefault(w => w.Name == name);
		}

		public void Add(Entity entity)
		{
			if (entities.Any(w => w == entity)) return;
			entities.Add(entity);
		}

		internal void Remove(Entity entity)
		{
			entities.Remove(entity);
			entity.Release();
		}
	}
}
