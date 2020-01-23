
////////////////////////STRUCTS AND STUFF////////////////////////

////////////////////////COMPONENTS////////////////////////
flecs::component<ActionToken> ActionToken_c(world, "ActionToken");

////////////////////////SYSTEMS////////////////////////
flecs::system<ActionToken> ActionIO_s(world, "ActionIOSystem");
auto registerActionIOSystems = [&]() {
	ActionIO_s.action([&](flecs::rows rows, flecs::column<ActionToken> token) {
		for (auto row : rows) {
			Card* card = rows.entity(row).get_ptr<Card>();
			if (card != nullptr) {
				TargetInfo info = TargetsExist(rows.entity(row).id());
				char target;
				bool oktogo = false;
				while (!oktogo)
				{
					//display board

					//player input
					if (info.leftTarget != 0 || info.rightTarget != 0) {
						printf("Choose Target: L/R");
						std::cin >> target;
					}

					//input validation
					if (target == 0 || target == 'l' || target == 'L' || target == 'r' || target == 'R') {
						//add attack
						rows.entity(row).set<Attack>({ (target == 'r' || target == 'R') ? (info.rightTarget) : (info.leftTarget), card->damage});
						oktogo = true; //why not just break?
					}
					else {
						printf("Invalid Entry");
					}
				}
				
				//remove token
				rows.entity(row).remove<ActionToken>();
			}
			//Hand* hand = rows.entity(row).get_ptr<Hand>();
			//if (hand != nullptr) {
			//	//player hand actions
			//}
		}
	});
};

////////////////////////ENTITIES////////////////////////
