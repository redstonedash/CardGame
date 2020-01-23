////////////////////////STRUCTS AND STUFF////////////////////////
struct Card;
struct Hand;
struct Player;
struct TargetInfo;
TargetInfo TargetExists(flecs::entity_t id);
////////////////////////COMPONENTS////////////////////////
flecs::component<ActionToken> ActionToken_c(world, "ActionToken");

////////////////////////SYSTEMS////////////////////////
flecs::system<ActionToken> ActionIO_s(world, "ActionIOSystem");
auto registerActionIOSys = [&]() {
	ActionIO_s.action([&](flecs::rows rows, flecs::column<ActionToken> token) {
		for (auto row : rows) {
			Card* card = rows.entity(row).get_ptr<Card>();
			if (card != nullptr) {
				TargetInfo info = TargetExists(rows.entity(row).id());
				char target;
				if (info.leftTargetExists || info.rightTargetExists) {
					printf("Choose Target: L/R");
					std::cin >> target;
				}
					
					//check if valid
				//card performs action
				//remove token
			}
			Hand* hand = rows.entity(row).get_ptr<Hand>();
			if (hand != nullptr) {
				//player hand actions
			}
		}
	});
};

////////////////////////ENTITIES////////////////////////
