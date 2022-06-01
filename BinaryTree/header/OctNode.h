
#include <memory>

template<typename K, typename T>
class OctNode {
public:

    Node(tuple <K, K, K> key, T Value);
    ~Node();

    tuple <K, K, K> key;

    T value;

    unique_ptr<OctNode> a;
    unique_ptr<OctNode> b;
    unique_ptr<OctNode> c;
    unique_ptr<OctNode> d;
    unique_ptr<OctNode> e;
    unique_ptr<OctNode> f;
    unique_ptr<OctNode> g;
    unique_ptr<OctNode> h;

};

// (0 or 1) (0 or 1) (0 or 1)

// 8 way 

/*
    (0, 0, 0)
    (0, 0, 1)
    (0, 1, 1)
    (1, 1, 1)
    (1, 1, 0)
    (1, 0, 0)
    (1, 0, 1)
    (0, 1, 0)
*/