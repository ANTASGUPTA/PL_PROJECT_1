#include "expr.h"
#include "stdlib.h"
#include "stdio.h"


struct Expr *mk_plus(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = PLUS;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_minus(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = MINUS;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_times(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret =  malloc(sizeof(struct Expr));
    ret->type = TIMES;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_div(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = DIV;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_float(float f) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = FLOAT;
    ret->literal = f;

    return ret;
}

/* This function should create the expr (1 + (4 * 5))
 * using the above constructors.
 */
struct Expr *mk_expr1() {
    return mk_plus(mk_float(1),mk_times(mk_float(4),mk_float(5)));
}

/* This function should create the expr (1 + (7 / 8))
 * using the above constructors.
 */
struct Expr *mk_expr2() {
    return mk_plus(mk_float(1),mk_div(mk_float(7),mk_float(8)));
}

/* This function should create the expr ((1 / 3) - (4 / (2 + 3)))
 * using the above constructors.
 */
struct Expr *mk_expr3() {
    return mk_minus(mk_div(mk_float(1),mk_float(3)),mk_div(mk_float(4),mk_plus(mk_float(2),mk_float(3))));
}


/*
 * This function should free all memory associated 
 * with the given AST.
*/
void free_expr(struct Expr* e) {
    if(!e or e == NULL) 
        return;
    if(e->type != FLOAT){
        free_expr(e->subexprs.e1);
        free_expr(e->subexprs.e2);
    }
    free(e);
}

/*
 * This function should evaluate the given AST and
 * return the floating-point result.
*/
float eval(struct Expr* e) {
    if(e==NULL){
        return 0.0;
    }
    if(e->type==FLOAT){
        return e->literal;
    }
    else if(e->type==PLUS){
        return eval(e->subexprs.e1) + eval(e->subexprs.e2);
    }
    else if(e->type==MINUS){
        return eval(e->subexprs.e1) - eval(e->subexprs.e2);
    }
    else if(e->type==TIMES){
        return eval(e->subexprs.e1) * eval(e->subexprs.e2);
    }
    else if(e->type==DIV){
        if(denominator == 0.0f)
            {
                printf("Divide by zero error.") /*To Handle the Zero divisible Error*/
            
                exit(1);  
            }
        else{
            return eval(e->subexprs.e1) / eval(e->subexprs.e2);
        }
        
    }
    return 0.0;
}