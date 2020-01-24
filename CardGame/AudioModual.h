////////////////////////STRUCTS AND STUFF////////////////////////
struct MusicPlayer
{

};

////////////////////////COMPONENTS////////////////////////
flecs::component<MusicPlayer> MusicPlayer_c(world, "MusicPlayer");

////////////////////////SYSTEMS////////////////////////
flecs::system<MusicPlayer> MusicPlayer_s(world, "MusicPlayerSystem");
auto registerMusicSystems = [&]() {
	MusicPlayer_s.action([&](flecs::rows rows, flecs::column<MusicPlayer> player) {
		for (auto row : rows) {
			UpdateMusicStream(music);
			if (GetMusicTimePlayed(music) / GetMusicTimeLength(music) >= 1.0f) {
				StopMusicStream(music);
				PlayMusicStream(music);
			}
		}
	});
};
