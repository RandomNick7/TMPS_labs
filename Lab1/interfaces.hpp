//A value printing interface for later...
class IValPrinter{
	public:
		//printVal has 2 versions depending on arguments: 1 for a single number and 1 for arrays of numbers
		//This is done to avoid repeated calls to the first type or making arrays of size 1 for the second type
		virtual void printVal(float val) = 0;
		virtual void printVal(float val[], int size) = 0;
};

//=====================================//

//Both 2D and 3D things qualify as polytopes
class IPolytope{
	public:
		virtual void calcArea(IValPrinter* out) = 0;
};

//The perimeter is a concept relevant only for 2D shapes
class IShape_2D: public IPolytope{
	public:
		virtual void calcPerimiter(IValPrinter* out) = 0;
};

class ITriangle: public IShape_2D{
public:
	virtual void printSides(IValPrinter* out) = 0;
};

//The volume is a concept relevant only for 3D objects
class IVolume_3D: public IPolytope{
	public:
		virtual void calcVolume(IValPrinter* out) = 0;
};

