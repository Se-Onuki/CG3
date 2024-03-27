#include <iostream>
#include <tuple>
#include <concepts>

// Example ISystem interface
struct ISystem {
	/* virtual void Update() = 0;
	 virtual ~ISystem() = default;*/
};

// Sample implementations of ISystem
struct System1 : public ISystem {
	void Update() const {
		std::cout << "System1 Update\n";
	}
};

struct System2 : public ISystem {
	void Update() const {
		std::cout << "System2 Update\n";
	}
};

// Concept to check if a type is derived from ISystem
template<typename T>
concept IsSystem = std::is_base_of_v<ISystem, T>;

// Function to update systems in tuple
template<std::size_t Index = 0, IsSystem... Systems>
void UpdateSystems(const std::tuple<Systems...> &systems) {
	if constexpr (Index < sizeof...(Systems)) {
		std::get<Index>(systems).Update();
		UpdateSystems<Index + 1>(systems);
	}
}

int main() {
	// Create a tuple with systems
	std::tuple<System1, System2> systems;

	// Call Update on each system in the tuple
	UpdateSystems(systems);

	return 0;
}
