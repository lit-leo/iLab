typedef struct st {
    double *array;
    int leng;
    int last;
} stack_s;

void stack_ctor(stack_s *this, int qty)
{
    if (qty <= 0)
        {
        printf("Error. Invalid quantity of elements.");
        exit(4);
        }
    this->array = (double *)calloc(qty, sizeof(double));
    this->leng = qty;
    this->last = -1;

}

void stack_dtor(stack_s *this)
{
    free(this->array);
    this->leng = -2;
    this->last = -2;
}

int stack_ok(stack_s this)
{
    if ((this.array != NULL) &&
        (this.leng > 0) && (this.last >= -1) &&
         (this.leng >= this.last))
            return 1;
    else
            return 0;
}

void stack_dump(stack_s this)
{
    int i = 0;
    printf("Adress of array is %lg\n", this.array);
    printf("Length is %d; Number of the last element is %d\n", this.leng, this.last);
    printf("Elements of array are:\n");
    for (i = 0; i < (this.last+1); i++)
        printf("%lg ", this.array[i]);
    printf("\n");
}

int push(stack_s *this, double x)
{
    if (stack_ok(*this) == 0)
        {
        printf("Invalid stack");
        return 0;
        }
    if ((this->last +1) == this->leng)
        {
        this->array = (double *)realloc(this->array,(this->leng+1)*(sizeof(double)));
        this->leng++;
        }
    if (stack_ok(*this) == 0)
        {
        printf("Falure with memory reallocation");
        return 0;
        }
    this->array[(this->last)+1] = x;
    this->last++;
    if (stack_ok(*this))
        return 1;
    else
        {
        printf("Got invalid stack after push");
        return 0;
        }
}

double pop(stack_s *this)
{
    double temp = 0;

    if (stack_ok(*this) && !(this->last == -1))
    {
        temp = this->array[this->last];
        this->last--;
        return temp;
    }
    else
        {printf("Error while trying to pop an element!");
        exit(3);
        }
}

int isEmpty(stack_s this)
{
    if (stack_ok(this) == 0)
        {
        printf("Invalid stack");
        exit(2);
        }
    if (this.last == -1)
        return 1;
    if (this.last > -1)
        return 0;
}
