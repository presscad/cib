#pragma  once
#include "context.h"
#include "shape.h"
#include <vector>

#include "__zz_cib_internal/composite-predef.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace Graphics
{
  typedef std::vector<Graphics::Shape*> Shapes;
  class Composite : public ::Graphics::Shape
  {
  public:
    Composite(Composite&& rhs);
  public:
    Composite(Composite const & );
    ~Composite();
    Composite();
    void Add(Shape* shape);
    size_t NumShapes() const;
    Shape* ShapeAt(size_t idxShape) const;
    /**
     * @return Area of this shape object.
     */
    virtual double Area() const;
    /**
     * @return Perimeter of this shape object.
     */
    virtual double Perimeter() const;
    /**
     * Draws this shape on a given device context.
     */
    virtual void Draw(Context* ctx) const;
    static Composite* CreateCompositeOfRectAndCircle();

  private:
    __ZZ_CIB_CLASS_INTERNAL_DEF(Composite, Graphics::Composite);
  };
}

#include "__zz_cib_internal/composite-postdef.h"
