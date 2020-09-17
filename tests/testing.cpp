#include <iostream>
#include <MyCEL/types/strongtype.hpp>
#include <MyCEL/types/operators.hpp>

struct Vec3D
{
	double xyz[3];
};
struct MyInt2_Tag{};
//static_assert(std::is_fundamental_v<Vec3D>);
using Strong1 = StrongType<int, struct MyInt1_Tag>;
using Strong2 = StrongType<int, struct MyInt2_Tag>;
using Strong3 = StrongType < Vec3D, MyInt2_Tag > ;
static_assert(sizeof(MyInt2_Tag) == 1);
static_assert(sizeof(Strong2) == sizeof(int));

using MySkilledType = SkilledStrongType<Vec3D, struct MyTagTest>;
using MySkilledType2 = SkilledStrongType<Vec3D, struct MyTagTest2, Add>;
using MySkilledType3 = SkilledStrongType<Vec3D, struct MyTagTest2, Increment>;
using MySkilledType4 = SkilledStrongType<int, struct MyTagTest2, Add>;
//static_assert(MySkilledType{ 1,2,3 } == 1);
//static_assert(MySkilledType{ 1 } == MySkilledType2{ 1 });
static_assert(sizeof(Vec3D) == 3 * sizeof(double));
static_assert(sizeof(Strong3) == sizeof(Vec3D));

//void function_on_int(int bla)
//{
//	std::cout << __FUNCSIG__ <<  '\n' << "called with value of: " << bla << '\n';
//}
//void function_on_intref(const int & bla)
//{
//	std::cout << __FUNCSIG__ << '\n' << "called with value of: " << bla << '\n';
//}
//void function_On_StrongInt1(Strong1 bla) {
//	std::cout << __FUNCSIG__ << '\n' << "called with value of: " << bla << '\n';
//};


int main()
{
	MySkilledType2 a{ Vec3D{1,2,3} };// == MySkilledType{ 1,2,3 };
	MySkilledType2 a2{ Vec3D{1,2,3} };
	//MySkilledType3 c1{ Vec3D{1,2,3} };
	//MySkilledType3 c2{ Vec3D{1,2,3} };
	//c1 += c2;
	MySkilledType4 c1{ 2 };
	MySkilledType4 c2{ 3 };
	auto c = c1 + c2;
	//auto c = a + a2;

	//auto whatvec = Vec3D{ 1,2,3 } +Vec3D{ 3,2,1 };
	int i = 1;
	Strong1 strong1{ i };
	Strong2 strong2{ i };
	Strong1 strong1deduced { strong1 +i  };
	//int j = strong1 + strong2;			// does not compile due to deleted operator+
	int j = strong1 + 1;
	strong1 += 1;
	//strong1 = !strong2;
	// Strong1 sj = strong2;			// does not compile since Strong1 and Strong2 are different
	 //Strong1 sj = strong1 + strong2;	// does not compile since no conversion from int -> Strong1
	 //Strong1 sj = strong1 + strong2;	// does not compile since no conversion from int -> Strong1
	//Strong1 sj{ strong1 + strong2 };	// does compile due to deleted operator+
	Strong1 si = strong1;
	//function_on_int(strong1);			// uses implicit conversion
	//function_on_intref(strong1);		// uses implicit conversion
	//function_On_StrongInt1(strong1);	//
	//function_On_StrongInt1( i );		// does not compile since there is no implicit conversion from int -> Strong1
	//function_On_StrongInt1({ i });		// does not compile since construction of Strong1 is explicit with an int 
	//function_On_StrongInt1(strong2);  // does not compile since there is no implicit conversion from Strong2 -> MyStrong1, although Strong2 -> int is possible
	return 0;
}