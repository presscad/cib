// DO NOT EDIT THIS FILE

#pragma once

namespace __zz_cib_ { namespace __zz_cib_classid {
	enum {
		//#= ::Graphics::Circle
		__Graphics__Circle = 1,
		//#= ::Graphics::Circle::__zz_cib_GenericProxy
		__Graphics__Circle____zz_cib_GenericProxy = 2,
		//#= ::Graphics::Composite
		__Graphics__Composite = 3,
		//#= ::Graphics::Composite::__zz_cib_GenericProxy
		__Graphics__Composite____zz_cib_GenericProxy = 4,
		//#= ::Graphics::Context
		__Graphics__Context = 5,
		//#= ::Graphics::Context::__zz_cib_GenericProxy
		__Graphics__Context____zz_cib_GenericProxy = 6,
		//#= ::Graphics::Ellipse
		__Graphics__Ellipse = 7,
		//#= ::Graphics::Ellipse::__zz_cib_GenericProxy
		__Graphics__Ellipse____zz_cib_GenericProxy = 8,
		//#= ::Graphics::LogContext
		__Graphics__LogContext = 9,
		//#= ::Graphics::LogContext::__zz_cib_GenericProxy
		__Graphics__LogContext____zz_cib_GenericProxy = 10,
		//#= ::Graphics::Rectangle
		__Graphics__Rectangle = 12,
		//#= ::Graphics::Rectangle::__zz_cib_GenericProxy
		__Graphics__Rectangle____zz_cib_GenericProxy = 13,
		//#= ::Graphics::Shape
		__Graphics__Shape = 14,
		//#= ::Graphics::Shape::__zz_cib_GenericProxy
		__Graphics__Shape____zz_cib_GenericProxy = 15,
		//#= ::Point
		__Point = 11,
		__zz_cib_next_class_id = 16
	};
}}

namespace __zz_cib_ { namespace Graphics { namespace Circle { namespace __zz_cib_methodid {
	enum {
		//#= Circle(float, float, float);
		__zz_cib_new_1 = 1,
		//#= virtual float Area() const;
		Area_2 = 2,
		//#= virtual float Perimeter() const;
		Perimeter_3 = 3,
		//#= virtual void Draw(Context*) const;
		Draw_4 = 4,
		//#= static Shape* CreateCircle(float, float, float);
		CreateCircle_5 = 5,
		//#= Circle(const Circle&);
		__zz_cib_new_6 = 6,
		//#= ~Circle()
		__zz_cib_delete_7 = 7,
		//#= __zz_cib_cast_to___Graphics__Shape
		__zz_cib_cast_to___Graphics__Shape_8 = 8,
		//#= __zz_cib_release_proxy
		__zz_cib_release_proxy_9 = 9,
		__zz_cib_next_method_id = 10
	};
}}}}

namespace __zz_cib_ { namespace Graphics { namespace Circle { namespace __zz_cib_GenericProxy { namespace __zz_cib_methodid {
	enum {
		//#= virtual float Area() const;
		Area_1 = 1,
		//#= virtual float Perimeter() const;
		Perimeter_2 = 2,
		//#= virtual void Draw(Context*) const;
		Draw_3 = 3,
		__zz_cib_next_method_id = 4
	};
}}}}}

namespace __zz_cib_ { namespace Graphics { namespace Composite { namespace __zz_cib_methodid {
	enum {
		//#= Composite();
		__zz_cib_new_1 = 1,
		//#= void Add(Shape*);
		Add_2 = 2,
		//#= size_t NumShapes() const;
		NumShapes_3 = 3,
		//#= Shape* ShapeAt(size_t) const;
		ShapeAt_4 = 4,
		//#= virtual float Area() const;
		Area_5 = 5,
		//#= virtual float Perimeter() const;
		Perimeter_6 = 6,
		//#= virtual void Draw(Context*) const;
		Draw_7 = 7,
		//#= static Composite* CreateCompositeOfRectAndCircle();
		CreateCompositeOfRectAndCircle_8 = 8,
		//#= Composite(const Composite&);
		__zz_cib_new_9 = 9,
		//#= ~Composite()
		__zz_cib_delete_10 = 10,
		//#= __zz_cib_cast_to___Graphics__Shape
		__zz_cib_cast_to___Graphics__Shape_11 = 11,
		//#= __zz_cib_get_class_id
		__zz_cib_get_class_id_12 = 12,
		//#= __zz_cib_release_proxy
		__zz_cib_release_proxy_13 = 13,
		__zz_cib_next_method_id = 14
	};
}}}}

namespace __zz_cib_ { namespace Graphics { namespace Composite { namespace __zz_cib_GenericProxy { namespace __zz_cib_methodid {
	enum {
		//#= virtual float Area() const;
		Area_1 = 1,
		//#= virtual float Perimeter() const;
		Perimeter_2 = 2,
		//#= virtual void Draw(Context*) const;
		Draw_3 = 3,
		__zz_cib_next_method_id = 4
	};
}}}}}

namespace __zz_cib_ { namespace Graphics { namespace Context { namespace __zz_cib_methodid {
	enum {
		//#= virtual void Line(float, float, float, float) = 0;
		Line_1 = 1,
		//#= virtual void Rect(float, float, float, float) = 0;
		Rect_2 = 2,
		//#= virtual void Circle(float, float, float) = 0;
		Circle_3 = 3,
		//#= virtual void Ellipse(float, float, float, float) = 0;
		Ellipse_4 = 4,
		//#= ~Context()
		__zz_cib_delete_5 = 5,
		//#= Context();
		__zz_cib_new_6 = 6,
		//#= __zz_cib_get_class_id
		__zz_cib_get_class_id_7 = 7,
		//#= __zz_cib_release_proxy
		__zz_cib_release_proxy_8 = 8,
		__zz_cib_next_method_id = 9
	};
}}}}

namespace __zz_cib_ { namespace Graphics { namespace Context { namespace __zz_cib_GenericProxy { namespace __zz_cib_methodid {
	enum {
		//#= virtual void Line(float, float, float, float) = 0;
		Line_1 = 1,
		//#= virtual void Rect(float, float, float, float) = 0;
		Rect_2 = 2,
		//#= virtual void Circle(float, float, float) = 0;
		Circle_3 = 3,
		//#= virtual void Ellipse(float, float, float, float) = 0;
		Ellipse_4 = 4,
		//#= ~Context()
		__zz_cib_delete_5 = 5,
		__zz_cib_next_method_id = 6
	};
}}}}}

namespace __zz_cib_ { namespace Graphics { namespace Ellipse { namespace __zz_cib_methodid {
	enum {
		//#= Ellipse(float, float, float, float);
		__zz_cib_new_1 = 1,
		//#= virtual float Area() const;
		Area_2 = 2,
		//#= virtual float Perimeter() const;
		Perimeter_3 = 3,
		//#= virtual void Draw(Context*) const;
		Draw_4 = 4,
		//#= Ellipse(const Ellipse&);
		__zz_cib_new_5 = 5,
		//#= ~Ellipse()
		__zz_cib_delete_6 = 6,
		//#= __zz_cib_cast_to___Graphics__Shape
		__zz_cib_cast_to___Graphics__Shape_7 = 7,
		//#= __zz_cib_release_proxy
		__zz_cib_release_proxy_8 = 8,
		__zz_cib_next_method_id = 9
	};
}}}}

namespace __zz_cib_ { namespace Graphics { namespace Ellipse { namespace __zz_cib_GenericProxy { namespace __zz_cib_methodid {
	enum {
		//#= virtual float Area() const;
		Area_1 = 1,
		//#= virtual float Perimeter() const;
		Perimeter_2 = 2,
		//#= virtual void Draw(Context*) const;
		Draw_3 = 3,
		__zz_cib_next_method_id = 4
	};
}}}}}

namespace __zz_cib_ { namespace Graphics { namespace LogContext { namespace __zz_cib_methodid {
	enum {
		//#= LogContext();
		__zz_cib_new_1 = 1,
		//#= ~LogContext()
		__zz_cib_delete_2 = 2,
		//#= virtual void Line(float, float, float, float) override;
		Line_3 = 3,
		//#= virtual void Rect(float, float, float, float) override;
		Rect_4 = 4,
		//#= virtual void Circle(float, float, float) override;
		Circle_5 = 5,
		//#= virtual void Ellipse(float, float, float, float) override;
		Ellipse_6 = 6,
		//#= LogContext(const LogContext&);
		__zz_cib_new_7 = 7,
		//#= __zz_cib_cast_to___Graphics__Context
		__zz_cib_cast_to___Graphics__Context_8 = 8,
		//#= __zz_cib_release_proxy
		__zz_cib_release_proxy_9 = 9,
		__zz_cib_next_method_id = 10
	};
}}}}

namespace __zz_cib_ { namespace Graphics { namespace LogContext { namespace __zz_cib_GenericProxy { namespace __zz_cib_methodid {
	enum {
		//#= virtual void Line(float, float, float, float) override;
		Line_1 = 1,
		//#= virtual void Rect(float, float, float, float) override;
		Rect_2 = 2,
		//#= virtual void Circle(float, float, float) override;
		Circle_3 = 3,
		//#= virtual void Ellipse(float, float, float, float) override;
		Ellipse_4 = 4,
		__zz_cib_next_method_id = 5
	};
}}}}}

namespace __zz_cib_ { namespace Graphics { namespace Rectangle { namespace __zz_cib_methodid {
	enum {
		//#= Rectangle(float, float, float, float);
		__zz_cib_new_1 = 1,
		//#= virtual float Area() const;
		Area_2 = 2,
		//#= virtual float Perimeter() const;
		Perimeter_3 = 3,
		//#= virtual void Draw(Context*) const;
		Draw_4 = 4,
		//#= Rectangle(const Rectangle&);
		__zz_cib_new_5 = 5,
		//#= ~Rectangle()
		__zz_cib_delete_6 = 6,
		//#= __zz_cib_cast_to___Graphics__Shape
		__zz_cib_cast_to___Graphics__Shape_7 = 7,
		//#= __zz_cib_release_proxy
		__zz_cib_release_proxy_8 = 8,
		__zz_cib_next_method_id = 9
	};
}}}}

namespace __zz_cib_ { namespace Graphics { namespace Rectangle { namespace __zz_cib_GenericProxy { namespace __zz_cib_methodid {
	enum {
		//#= virtual float Area() const;
		Area_1 = 1,
		//#= virtual float Perimeter() const;
		Perimeter_2 = 2,
		//#= virtual void Draw(Context*) const;
		Draw_3 = 3,
		__zz_cib_next_method_id = 4
	};
}}}}}

namespace __zz_cib_ { namespace Graphics { namespace Shape { namespace __zz_cib_methodid {
	enum {
		//#= virtual float Area() const = 0;
		Area_1 = 1,
		//#= virtual float Perimeter() const = 0;
		Perimeter_2 = 2,
		//#= virtual void Draw(Context*) const = 0;
		Draw_3 = 3,
		//#= ~Shape()
		__zz_cib_delete_4 = 4,
		//#= Shape();
		__zz_cib_new_5 = 5,
		//#= __zz_cib_get_class_id
		__zz_cib_get_class_id_6 = 6,
		//#= __zz_cib_release_proxy
		__zz_cib_release_proxy_7 = 7,
		__zz_cib_next_method_id = 8
	};
}}}}

namespace __zz_cib_ { namespace Graphics { namespace Shape { namespace __zz_cib_GenericProxy { namespace __zz_cib_methodid {
	enum {
		//#= virtual float Area() const = 0;
		Area_1 = 1,
		//#= virtual float Perimeter() const = 0;
		Perimeter_2 = 2,
		//#= virtual void Draw(Context*) const = 0;
		Draw_3 = 3,
		//#= ~Shape()
		__zz_cib_delete_4 = 4,
		__zz_cib_next_method_id = 5
	};
}}}}}

namespace __zz_cib_ { namespace Point { namespace __zz_cib_methodid {
	enum {
		//#= Point(float, float);
		__zz_cib_new_1 = 1,
		//#= float X() const;
		X_2 = 2,
		//#= void X(float);
		X_3 = 3,
		//#= float Y() const;
		Y_4 = 4,
		//#= void Y(float);
		Y_5 = 5,
		//#= Point operator +(const Point&) const;
		__zz_cib_OperatorPlus_6 = 6,
		//#= Point operator -(Point) const;
		__zz_cib_OperatorMinus_7 = 7,
		//#= Point(const Point&);
		__zz_cib_new_8 = 8,
		//#= ~Point()
		__zz_cib_delete_9 = 9,
		__zz_cib_next_method_id = 10
	};
}}}

