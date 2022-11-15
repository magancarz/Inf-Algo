
#include <stdio.h>


/** \brief Java style Doc String - Foo function */
int foo();

int bar(); /**< Bar function */

/// .NET Style Doc String
int g_global_var = 1;


int baz() {
	printf("mleko");
}
// */

/*! Global variable
 *  ... */
volatile int g_global;

//! Main
int main(int argc, const char* argv)
{
    printf("/* foo bar");
    //*/ bar();

    // \
    /*
    baz();
    /*/
    foo();
    //*/

/\
/*
    baz();
/*/
    foo();
//*/

    return 1;
}
