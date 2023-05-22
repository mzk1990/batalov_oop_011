#pragma once
#include "Object.h"
class TaskFactory
{
public:
    static Object* makeRandomObject(  ) {
        switch ( rand(  ) % 3 ) {
        case 0:
            return make_plus(  );
        case 1:
            return make_minus(  );
        case 2:
            return make_multiply(  );
        default:
            return nullptr;
        }
    }

    static Object* make_plus(  ) {
        double x = randomDouble( -1000, 1000 );
        double y = randomDouble( -1000, 1000 );
        return new BinaryTask( "plus", x, y );
    }
    static Object* make_minus(  ) {
        double x = randomDouble( -1000, 1000 );
        double y = randomDouble( -1000, 1000 );
        return new BinaryTask( "minus", x, y );
    }
    static Object* make_multiply(  ) {
        double x = randomDouble( -1000, 1000 );
        double y = randomDouble( -1000, 1000 );
        return new BinaryTask( "multiply", x, y );
    }
private:
    static double randomDouble( double min, double max ) {
        double random = ( double )rand(  ) / RAND_MAX;
        return min + random * ( max - min );
    }
};