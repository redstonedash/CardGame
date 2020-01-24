
////////////////////////STRUCTS AND STUFF////////////////////////

////////////////////////COMPONENTS////////////////////////
flecs::component<ActionToken> ActionToken_c(world, "ActionToken");

////////////////////////SYSTEMS////////////////////////
flecs::system<ActionToken, Card> ActionIO_s(world, "ActionIOSystem");
auto registerActionIOSystems = [&]() {
	ActionIO_s.action([&](flecs::rows rows, flecs::column<ActionToken> token, flecs::column<Card> card) {
		for (auto row : rows) {
			
				TargetInfo info = TargetsExist(rows.entity(row).id());
				char target = 0;
				bool oktogo = false;
				printf("%"  PRId64 "'s turn", rows.entity(row).id());
				//display board

				//player input
				if (info.leftTarget != 0 || info.rightTarget != 0) {
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						target = 'l';
					}
					else if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
						target = 'r';
					}
					else {
						target = 'x';
					}
				}

				//input validation
				if (target == 0 || target == 'l' || target == 'r') {
					//add attack
					rows.entity(row).set<Attack>({ (target == 'r') ? (info.rightTarget) : (info.leftTarget), card->damage});
					//AttackSystem_s.run();
				}
			}
		
		//Hand* hand = rows.entity(row).get_ptr<Hand>();
		//if (hand != nullptr) {
		//	//player hand actions
		//}
	});
};

////////////////////////ENTITIES////////////////////////
