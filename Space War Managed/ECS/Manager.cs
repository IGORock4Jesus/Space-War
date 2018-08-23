using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed.ECS
{
	class Manager
	{
		readonly List<System> systems = new List<System>();

		public void AddSystem<T>(T system) where T : System
		{
			if (systems.Any(w => w is T))
				return;

			systems.Add(system);
		}

		public T Get<T>() where T : System
		{
			return systems.FirstOrDefault(w => w is T) as T;
		}

		public void Render(Renderer renderer)
		{
			foreach (var s in systems)
			{
				s.Render(renderer);
			}
		}

		public void Update(float time)
		{
			foreach (var s in systems)
			{
				s.Update(time);
			}
		}
	}
}
