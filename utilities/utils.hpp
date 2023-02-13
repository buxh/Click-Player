// removes secure warnings "_CRT_SECURE_NO_WARNINGS"
#pragma warning(disable:4996)

namespace utils {

	constexpr auto minecraft = "LWJGL";
	std::string getkeyname(const int id);
	inline char* username;
	inline std::string clicktype;
	inline int count;
	inline int cps;
	inline std::string recdate;

	auto initialize_console() -> void;
	void title();
	void init();
	void show_logo();
	void launch_threads();
	int set_priority_class();
	double calculate_cps();
	void set_keybind();
	void separator();
	
}