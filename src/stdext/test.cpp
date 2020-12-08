
#include "std_extensions.h"
using namespace stdext;

//#include "get_array_size.h"
static_assert(array_size< std::array<double, 10> > == 10);

//#include "is_arithmetic_container.h"
static_assert(is_arithmetic_container_v<std::vector<double>>);
static_assert(is_arithmetic_container_v<std::vector<double>&>);
static_assert(!is_arithmetic_container_v<std::vector<std::string>>);
static_assert(!is_arithmetic_container_v<std::string>);


//#include "is_associative_container.h"
namespace
{
    static_assert(!is_associative_container_v<std::array<double, 5>>);
    static_assert(!is_associative_container_v<std::vector<float>>);
    static_assert(!is_associative_container_v<std::deque<int>>);
    static_assert(!is_associative_container_v<std::list<std::uint16_t>>);

    //
    static_assert(is_associative_container_v<std::set<float>>);
    static_assert(is_associative_container_v<std::multiset<float>>);
    static_assert(is_associative_container_v<std::map<std::uint16_t, float>>);
    static_assert(is_associative_container_v<std::multimap<std::uint16_t, float>>);
    static_assert(is_associative_container_v<std::multiset<float>>);
    static_assert(is_associative_container_v<std::unordered_set<float>>);
    static_assert(is_associative_container_v<std::unordered_multiset<float>>);
    static_assert(is_associative_container_v<std::unordered_map<std::uint16_t, float>>);
    static_assert(is_associative_container_v<std::unordered_multimap<std::uint16_t, float>>);

    //These are not containers due to lack of some iterators or members! (They use one of the above internally but have a different interface!)
    static_assert(!is_associative_container_v<std::forward_list<float>>); //Lacks size() method !
    static_assert(!is_associative_container_v<std::stack<float>>);
    static_assert(!is_associative_container_v<std::queue<float>>);
    static_assert(!is_associative_container_v<std::priority_queue<float>>);
}

//#include "is_boost_multiarray.h"
//#include "is_callable.h"
//#include "is_complex.h"
namespace
{
    static_assert(is_complex_v<std::complex<double>>,"Static test failed");
    static_assert(is_complex_v<std::complex<float>>, "Static test failed");
    static_assert(is_complex_v<std::complex<long double>>, "Static test failed");
    static_assert(is_complex_v<std::complex<std::size_t>>, "Static test failed");
}

//#include "is_container.h"
//#include "is_dectected.h"
//#include "is_eigen3_type.h"
//#include "is_memory_sequentiel_container.h"
namespace
{
    using MemSeq1 = std::vector<std::string>;
    using MemSeq2 = std::array<float,20>;
    using MemSeq3 = std::vector<std::uint16_t>;
    using NotMemSeq = std::list<std::uint64_t>;
    using NotMemSeq2 = std::vector<MemSeq2>;

    static_assert(is_memory_sequentiel_container_v<MemSeq1>);
    static_assert(is_memory_sequentiel_container_v<MemSeq2>);
    static_assert(is_memory_sequentiel_container_v<MemSeq3>);

    static_assert(!is_memory_sequentiel_container_v<NotMemSeq>);
    static_assert(!is_memory_sequentiel_container_v<NotMemSeq2>);
}

//#include "is_nested_arithmetic_container.h"
namespace {
    using NestedContainer = std::vector<std::vector<std::vector<double>>>;
    static_assert(!is_arithmetic_container_v<NestedContainer>);
    static_assert(is_container_v<std::decay_t<NestedContainer>::value_type>);
    static_assert(is_nested_container_v<NestedContainer>);
    static_assert(is_nested_arithmetic_container_helper_v<NestedContainer>);
    static_assert(is_nested_arithmetic_container_v<NestedContainer>);
}
namespace {
    using NestedContainer1 = std::vector<std::vector<double>>;
    static_assert(!is_arithmetic_container_v<NestedContainer1>);
    static_assert(is_container_v<std::decay_t<NestedContainer1>::value_type>);
    static_assert(is_nested_container_v<NestedContainer1>);
    static_assert(is_nested_arithmetic_container_helper_v<NestedContainer1>);
    static_assert(is_nested_arithmetic_container_v<NestedContainer1>);
}
namespace {
    using NestedContainer2 = std::vector<double>;
    static_assert(is_arithmetic_container_v<NestedContainer2>);
    static_assert(!is_container_v<std::decay_t<NestedContainer2>::value_type>);
    static_assert(!is_nested_container_v<NestedContainer2>);
    static_assert(is_nested_arithmetic_container_helper_v<NestedContainer2>); // The helper is true if is_arithmetic_container_v is true
    static_assert(!is_nested_arithmetic_container_v<NestedContainer2>);
}
//#include "is_nested_container.h"
namespace
{
    using NestedContainer3 = std::vector<std::array<std::vector<double>,5>>;
    static_assert(is_container_v<NestedContainer3>);
    static_assert(is_container_v<std::decay_t<NestedContainer3>::value_type>);
    static_assert(is_nested_container_v<NestedContainer3>);
    static_assert(std::is_same<double, get_nested_type_t<NestedContainer3>>::value);

    using IsNotNested = std::vector<double>;

    static_assert(is_container_v<IsNotNested>);
    static_assert(!is_container_v<std::decay_t<IsNotNested>::value_type>);
    static_assert(!is_nested_container_v<IsNotNested>);
    static_assert(std::is_same<double, get_nested_type_t<IsNotNested>>::value);
}

//#include "is_resizeable_container.h"
namespace //Test
{
    using Resizeable = std::vector<double>;
    using NotResizeable = std::map<std::uint16_t, double>;

    static_assert(is_resizeable_container_v<Resizeable>);
    static_assert(!is_resizeable_container_v<NotResizeable>);
}

//#include "is_sequentiel_container.h"
//#include "is_string.h"
//Tests
static_assert(stdext::is_string_v<std::string>);
static_assert(stdext::is_string_v<std::string&>);
static_assert(stdext::is_string_v<const std::string&>);
static_assert(stdext::is_string_v<volatile std::string&>);

int main()
{
    return 0;
}
