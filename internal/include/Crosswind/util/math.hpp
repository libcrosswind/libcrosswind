
namespace cw{
	class math{
	public:
		template<typename T>
		static T clamp(T d, T min, T max){
			T t = d < min ? min : d;
			return t > max ? max :t;
		}
	};
}