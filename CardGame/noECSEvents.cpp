#include <vector>
template<typename ... Params>
class EventDispatcher {
	std::vector<void (*)(Params...)> Procedures = std::vector<(*)(Params...)>();
	void operator()(Params... params) {
		for (auto proc : Procedures) {
			proc(params);
		}
	}
};