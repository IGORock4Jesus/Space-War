using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed.ECS
{
	class Entity
	{
		public string Name { get; set; } = "no_name";
		List<Component> components = new List<Component>();
		public Component[] Components => components.ToArray();

		public void Add<T>(T component) where T : Component
		{
			if (components.Any(w => w is T)) return;

			components.Add(component);
		}

		internal T Get<T>() where T : Component
		{
			return components.First(w => w is T) as T;
		}

		public void Release()
		{
			components.ForEach(w => w.Release());
		}
	}
}
