#include "flecs.h";
#include "flecs/flecs.hpp";
struct DeleteMe {
};

int main() {
	flecs::world wrld = flecs::world();
	flecs::component<DeleteMe> DeleteMe_c = flecs::component<DeleteMe>(wrld, "CardVisuals");
	flecs::system<DeleteMe> DeleteSystem_s(wrld, "DeleteSystem");
	DeleteSystem_s.action([&](flecs::rows rows, flecs::column<DeleteMe> dm) {
		for (auto row : rows) {
			rows.entity(row).remove<DeleteMe>();
		}
	});
	flecs::entity(wrld, "idk").add<DeleteMe>();
	wrld.progress(0);
	wrld.progress(0);
	wrld.progress(0);
}