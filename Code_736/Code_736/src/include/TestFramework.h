#ifndef _TEST_FRAMEWORK_H_INCLUDED_
#define _TEST_FRAMEWORK_H_INCLUDED_

#define PRINT(type, var,val,condition) {printf("%s: In %s at line %d the var '%s=%d' %s val '%d'\n", type,__FILE__, __LINE__, #var, var,condition, val); return;}

#define PRINT_FATAL(var, val, condition) PRINT("FATAL", var,val, condition)
#define TEST_IS_EQ(var, val) if(var!=val)PRINT_FATAL(var, val,"IS NOT EQUAL TO")
#define TEST_IS_LT(var, val) if(var>=val)PRINT_FATAL(var, val,"IS GREATHER THAN OR EQUAL")
#define TEST_IS_GT(var, val) if(var<=val)PRINT_FATAL(var, val,"IS LESS THAN OR EQUAL TO")
#define TEST_IS_LT_EQ(var, val) if(var>val)PRINT_FATAL(var, val,"IS GREATHER THAN")
#define TEST_IS_GT_EQ(var, val) if(var<val)PRINT_FATAL(var, val,"IS LESS THAN")
#define TEST_IS_NO_EQ(var, val) if(var==val)PRINT_FATAL(var, val,"IS EQUAL TO")
#define TEST_ISPTR_EQ(var, val) TEST_IS_EQ(var, val)


#define PRINT2(type, modulename)printf("------------------------------------------------------------------------------------------------------------\n%s: The module '%s' in file %s at line %d is subjected to test\n------------------------------------------------------------------------------------------------------------\n", type, #modulename, __FILE__, __LINE__)
#define PRINT_MESSAGE(modulename) PRINT2("MESSAGE", modulename)
#define INIT_TESTING(modulename) PRINT_MESSAGE(modulename)


#endif