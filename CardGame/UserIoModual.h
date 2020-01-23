////////////////////////STRUCTS AND STUFF////////////////////////
struct ActionToken {

};
struct Card;
struct Hand;
////////////////////////COMPONENTS////////////////////////
flecs::component<ActionToken> ActionToken_c(world, "ActionToken");

////////////////////////SYSTEMS////////////////////////
flecs::system<ActionToken> ActionIO_s(world, "ActionIOSystem");
auto registerActionIOSys = [&]() {
	ActionIO_s.action([&](flecs::rows rows, flecs::column<ActionToken> token) {
		for (auto row : rows) {
			Card* card = rows.entity(row).get_ptr<Card>();
			if (card != nullptr) {
				//has left or right?
					//query left or right
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
