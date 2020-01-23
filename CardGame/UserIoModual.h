////////////////////////STRUCTS AND STUFF////////////////////////
struct Card;
struct Hand;
struct Player;
struct TargetInfo;
////////////////////////COMPONENTS////////////////////////
flecs::component<ActionToken> ActionToken_c(world, "ActionToken");

////////////////////////SYSTEMS////////////////////////
flecs::system<ActionToken> ActionIO_s(world, "ActionIOSystem");
auto registerActionIOSystems = [&]() {
	ActionIO_s.action([&](flecs::rows rows, flecs::column<ActionToken> token) {
		for (auto row : rows) {
			Card* card = rows.entity(row).get_ptr<Card>();
			if (card != nullptr) {
				TargetInfo info = TargetExists(rows.entity(row).id());
				char target;
				bool oktogo = false;
				while (!oktogo)
				{
					//display board

					//player input
					if (info.leftTargetExists || info.rightTargetExists) {
						printf("Choose Target: L/R");
						std::cin >> target;
					}

					//input validation
					if (target == 0 || target == 'l' || target == 'L' || target == 'r' || target == 'R') {
						oktogo = true;
					}
					else {
						printf("Invalid Entry");
					}
				}

				//remove token
				rows.entity(row).remove<ActionToken>();
			}
			Hand* hand = rows.entity(row).get_ptr<Hand>();
			if (hand != nullptr) {
				//player hand actions
			}
		}
	});
};

////////////////////////ENTITIES////////////////////////
