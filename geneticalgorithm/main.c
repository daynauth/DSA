#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<assert.h>
#include<math.h>

#define LINE_LENGTH 128
#define DIMENSION_LINE 5
#define DATA_START_LINE 8

#define createCity() malloc(sizeof(City))
#define createCities() malloc(sizeof(cityPtr) * dimension)

typedef struct {
    int id;
    double x;
    double y;
} City;

typedef City *cityPtr;

typedef struct chrom {
    cityPtr *path;
    double fitness;
    int size;
    int length; //total length of path
} _chromozone, *Chromozone;

typedef Chromozone *Population;

float randUniformPositive();
void shuffleArray(int *arr, int length);
void printArray(int *arr, int length);
void swap(cityPtr *a, cityPtr *b);
int weightSum(int *arr, int length);
int rouletteSelect(int *arr, int length);
int distance(double x1, double x2, double y1, double y2);

Chromozone loadCities(FILE *fp);
size_t get_dimension(char *line);

/*
 * Functions specific to the genetic algorithm will follow here
 *
 */
int calculate_tour_length(Chromozone tour);
int city_distance(cityPtr cityA, cityPtr cityB);
Chromozone new_chromozone();
Chromozone generate_random_chromozone(Chromozone base_chromozone);
void generate_random_path(cityPtr *path, int size);
Population generate_random_population(Chromozone base_chromozone, long size);
void free_population(Population p, long size);
int max_distance(Population p, long size);
int min_distance(Population p, long size);

void test();

int main(){
    time_t t;
    srand((unsigned) time(&t));

    char filename[] =  "lu980.tsp";
    long population_size = 1000;
    float crossover_rate = 0.6;

    FILE *fp = fopen(filename, "r");

    Chromozone base_chromozone = loadCities(fp);
    

    Population population = generate_random_population(base_chromozone, population_size);

    for(int i = 0; i < population_size; i++){
        population[i]->length = calculate_tour_length(population[i]);
        //printf("%lf\n", population[i]->length);
    }

    printf("max distance: %d\n", max_distance(population, population_size));
    printf("min distance: %d\n", min_distance(population, population_size));
    free_population(population, population_size);
    
    //double tour_length = calculate_tour_length(base_chromozone);

    //printf("%lf\n", tour_length);

    //printf("%lf\n", base_chromozone->path[900]->x);

    free(base_chromozone->path);
    free(base_chromozone);

    fclose(fp);


    test();
    return 0;
}

void test(){
    int parent1[] = {1,2,5,6,4,3,8,7};
    int parent2[] = {1,4,2,3,6,5,7,8};


}
int min_distance(Population p, long size){
    int min = p[0]->length;
    int i;

    for(i = 1; i < size; i++){
        if(p[i]->length < min)
            min = p[i]->length;
    }

    return min;
}

int max_distance(Population p, long size){
    double max = p[0]->length;
    int i;

    for(i = 1; i < size; i++){
        if(p[i]->length > max)
            max = p[i]->length;
    }

    return max;
}

Population generate_random_population(Chromozone base_chromozone, long size){
    Population p = malloc(sizeof(Chromozone) * size);

    assert(p != NULL);

    int i;
    for(int i = 0; i < size; i++){
        p[i] = generate_random_chromozone(base_chromozone); 
    }

    return p;
}

void free_population(Population p, long size){
    int i;

    for(i = 0 ; i < size; i++){
        free(p[i]->path);
        free(p[i]);
    }

    free(p);
}

Chromozone generate_random_chromozone(Chromozone base_chromozone){
    Chromozone c = new_chromozone();
    c->size = base_chromozone->size;
    c->path = malloc(sizeof(cityPtr) * c->size);
    memcpy(c->path, base_chromozone->path, sizeof(cityPtr) * c->size);

    generate_random_path(c->path, c->size);
    return c;
}

Chromozone new_chromozone(){
    Chromozone c = malloc(sizeof(_chromozone));
    assert(c != NULL);
    return c;
}

void generate_random_path(cityPtr *path, int length){
    int i, j;
    
    for(i = length - 1; i > 0; i--){
        j = rand () % i;
        swap(path + i, path + j);
    }
}

void swap(cityPtr *a, cityPtr *b){
   cityPtr temp = *a;
    *a = *b;
    *b = temp;
}


int calculate_tour_length(Chromozone tour){
   int i;
   int length = 0;

   for(i = 0; i < tour->size - 1; i++){
        length += city_distance(tour->path[i], tour->path[i + 1]);
   }

   length += city_distance(tour->path[tour->size - 1], tour->path[0]);

   return length;
}

int city_distance(cityPtr cityA, cityPtr cityB){
    return distance(cityA->x, cityB->x, cityA->y, cityB->y);
}

int distance(double x1, double x2, double y1, double y2){
    double dx = x1 - x2;
    double dy = y1 - y2;
    return (int)sqrt(dx*dx + dy*dy);
}

Chromozone  loadCities(FILE *fp){
    cityPtr *cities;
    char line[LINE_LENGTH];
    size_t dimension = 0;

    unsigned int line_number = 1;
    size_t idx = 0;

    while(fgets(line, sizeof(line), fp) != NULL){
        if(line_number == DIMENSION_LINE){
            dimension = get_dimension(line);
            cities = malloc(sizeof(cityPtr) * dimension);

            assert(cities != NULL);
        }

        if(line_number >= DATA_START_LINE && idx <= dimension){
            cities[idx] = malloc(sizeof(City));
            assert(cities[idx] != NULL);

            sscanf(line, "%d %lf %lf", &cities[idx]->id, &cities[idx]->x, &cities[idx]->y);
            idx++;
        }

        line_number++;
    }


    Chromozone c = malloc(sizeof(_chromozone));
    c->path = cities;
    c->size = dimension;
    
    return c;
}

size_t get_dimension(char *line){
    char *dim = strrchr(line, ':');
    size_t dimension = 0;

    if(dim != NULL){
        sscanf(dim + 1, "%zu", &dimension);
    }else{
        fprintf(stderr, "Failed to get dimension from line %s!\n", line);
        exit(EXIT_FAILURE);
    }
    return dimension;
}


float randUniformPositive(){
    return (float) rand()/ RAND_MAX;
}


void printArray(int *arr, int length){
    int i;

    for(i = 0; i < length - 1; i++)
        printf("%d, ", arr[i]);
    
    printf("%d\n", arr[length - 1]);
}


int weightSum(int *arr, int length){
    int i, sum = 0;

    for(i = 0; i < length; i++)
        sum += arr[i];
    
    return sum;
}

int rouletteSelect(int *arr, int length){
    int sum = weightSum(arr, length), i;
    float value = randUniformPositive() * sum;

    for(i = 0; i < length; i++){
        value -= arr[i];
        if(value < 0)
            return i;
    }

    return length - 1;
}

