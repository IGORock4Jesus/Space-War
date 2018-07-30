#pragma once
#include <typeinfo>
#include <string>
#include <d3dx9.h>

namespace ECS
{
	constexpr size_t MAX_COMPONENTS = 100;
	constexpr size_t MAX_ENTITY_COMPONENTS = 8;

	class Component {
		const size_t hashType;

	public:
		Component(size_t hashType)
			: hashType{ hashType } {}

		virtual ~Component() {}

		const size_t GetHashType() const {
			return hashType;
		}
	};

	class Entity {
		std::string name;
		Component* components[MAX_ENTITY_COMPONENTS];

	public:
		Entity() {
			memset(components, 0, sizeof(Component*) * MAX_ENTITY_COMPONENTS);
		}

		void SetName(std::string name) { this->name = name; }
		const std::string GetName() const { return name; }

		template <typename T>
		void AddComponent(T* c) {
			static_assert(std::is_base_of<Component, T>::value, "T должен наследовать ECS::Component!");

			for (size_t i = 0; i < MAX_ENTITY_COMPONENTS; i++)
			{
				if (!components[i]) {
					components[i] = c;
					return;
				}
			}

			throw std::overflow_error("Объект не может содержать больше компонентов.");
		}

		template <typename T>
		T* GetComponent() {
			static_assert(std::is_base_of<Component, T>::value, "T должен наследовать ECS::Component!");

			auto tHash = typeid(T).hash_code();

			for (size_t i = 0; i < MAX_ENTITY_COMPONENTS; i++)
			{
				if (components[i] && components[i]->hashType == tHash) {
					return (T*)components[i];
				}
			}

			return nullptr;
		}
	};

	class SystemBase {

	};

	template <typename T>
	class System : public SystemBase {
		static_assert(std::is_base_of<Component, T>::value, "T должен наследовать ECS::Component!");

		T* components[MAX_COMPONENTS]{ 0 };

	protected:
		void GetComponents(__out T*** components) {
			*components = this->components;
		}

	public:
		virtual void Update(int elapsedTime) {}
		virtual void Render(LPDIRECT3DDEVICE9 device) {}

		void Add(T* component) {
			for (size_t i = 0; i < MAX_COMPONENTS; i++)
			{
				if (!components[i]) {
					components[i] = component;
					return;
				}
			}

			throw std::overflow_error("Система не может хранить больше компонентов.");
		}
	};

	template <typename T>
	size_t GetComponentHash() {
		static const size_t hash = typeid(T).hash_code();
		return hash;
	}
}
