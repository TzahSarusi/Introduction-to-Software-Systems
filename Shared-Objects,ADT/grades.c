#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "linked-list.h"
#include "grades.h"

/*defines*/
#define SUCCESS 0
#define FAILURE -1
#define MAX_GRADE 100
#define MIN_GRADE 0
#define NEXT 1

/*structs initials*/
struct type_student {
	struct list *grade_student;
	char* name;
	int id;
	int course_num;
	float average;
};

struct type_course {
	char* name_of_course;
	int grade;
};

struct grades {
	struct list* list_students;
};

/* Clone\Destroy functions declarations*/
int clone_student(void* argu, void** out);
void destroy_student_data(void* argu);
int clone_course(void* argu, void** out);
void destroy_course_data (void *argu);
/*grades_printer declaration*/
static int grades_printer(struct type_student *type_student,
							struct list *grade_student);


/* returns pointer to struct with the student name,id,num of courses,average*/
static int initial_student(struct list *list_pointer
							,const char *name
							,int id){
	struct type_student *student_data_new;
	int tmp;
	student_data_new=(struct type_student*)malloc(sizeof(struct type_student));
	student_data_new->name=(char*)malloc(sizeof(char*)*(strlen(name)+NEXT));
	if ( !(student_data_new) ||!(student_data_new->name)) {
			free(student_data_new->name);
			free(student_data_new);
			return SUCCESS;
	}
	else{
	(student_data_new-> id)=id;
	strcpy((student_data_new->name),name);
	student_data_new->average=MIN_GRADE;
	student_data_new->course_num = 0;
	student_data_new->grade_student = list_init(clone_course,
											destroy_course_data);
	tmp =list_push_back(list_pointer, student_data_new);
	list_destroy((student_data_new->grade_student));
	free(student_data_new->name);
	free(student_data_new);
	}
	return tmp;
}

/* if there is an error return 0, if all good then it will return a pointer
	to a struct with the course name, grade*/
static int initial_course(struct list *list, const char *name, int grade){
	int new_course;
	struct type_course *course_data_new;
	course_data_new=(struct type_course*)malloc(sizeof(struct type_course));
	course_data_new->name_of_course=(char*)
									malloc(sizeof(char*)*(strlen(name)+NEXT));
	if (!course_data_new->name_of_course ||!(course_data_new)) {
			free(course_data_new->name_of_course);
			free(course_data_new);
			return SUCCESS;
	}

	else{
	course_data_new-> grade = grade;
	strcpy((course_data_new->name_of_course),name);
	new_course=list_push_back(list, course_data_new);
	free(course_data_new->name_of_course);
	free(course_data_new);
	}
	return new_course;
}

/* if the course exists return 0, if not then it returns a pointer to 
	a struch that conatins course name,course,grade*/
static struct iterator* course_finder(const char* name, struct list* list) {
	struct iterator* course_current = list_begin(list);
	while (course_current) {
		struct type_course* course_current_data = list_get(course_current);
		const char* course_current_name =
						(course_current_data->name_of_course);
		if (!strcmp(course_current_name, name)) {
			return course_current;
		}
		else {
			course_current = list_next(course_current);
		}
	}
	return SUCCESS;
}

/*if the student exists returns a pointer with the id, if not returns 0*/
static struct iterator *id_searcher(int id,struct list *list){
	    struct iterator *student_current = list_begin(list);
		while(student_current){
			struct type_student *student_new=list_get(student_current);
			int id_new=(int)(student_new->id);
			if(id_new == id){
				return student_current;
			}
			else{
				student_current = list_next(student_current);
			}
		}
		return SUCCESS;
}

int grades_add_student(struct grades* grades, const char* name, int id) {
	if (!grades || !name || !id) {
		return FAILURE;
	}
	else {
		struct iterator* iterator_current = id_searcher(id,
											(grades->list_students));
		if (!iterator_current) {
			return (initial_student((grades->list_students), name, id));
		}
		else {
			return 	FAILURE;
		}
	}
	return FAILURE;
}

int grades_add_grade(struct grades* grades
					, const char* name
					, int id, int grade) {
	if (!id || (grade > MAX_GRADE) || (grade < MIN_GRADE) || !grades) {
		return FAILURE;
	}
	else {
		struct type_student* student_current_data;
		struct iterator* iterator_current = id_searcher(id,
											(grades->list_students));
		if (iterator_current) {
			student_current_data = list_get(iterator_current);
			if (!course_finder(name, (student_current_data->grade_student))) {
				
				int temp_num = student_current_data->course_num;
				float temp_avg = student_current_data->average;
				student_current_data->course_num = temp_num + NEXT;
				student_current_data->average =
						((temp_avg * temp_num + grade) / (temp_num + NEXT));


				return (initial_course((student_current_data->grade_student)
										, name, grade));
			}
			else {
				return FAILURE;
			}
		}
	}
	return FAILURE;
}

/* Calculates the average of a student*/
float grades_calc_avg(struct grades *grades, int id, char **out){
	if (!grades ||!out|| !id) {
		return FAILURE;
	}
	else{
		struct type_student *student_current_data;
		struct iterator *iterator_current = id_searcher(id,
										(grades->list_students));
		if(!iterator_current){
			
			/*return -1 if the id is not detectable*/
			return FAILURE;
		}
		else{
			student_current_data =list_get(iterator_current);
			char *out_tmp =(char*)malloc
						(sizeof(char*)*(strlen(student_current_data->name)+NEXT));
			strcpy(out_tmp, student_current_data->name);
			*out= out_tmp;
			return (student_current_data->average);
		}
	}
	return FAILURE;	
}


int grades_print_student(struct grades *grades, int id){
	if (!grades || !id) {
		return FAILURE;
	}
	else{
		struct iterator *student_current_iterator;
		struct type_student *student_current_data;
		student_current_iterator = (struct iterator*)id_searcher(id,
									(grades->list_students));
		student_current_data = list_get(student_current_iterator);
		if(!student_current_data){
			return FAILURE;
		}
		else{
			return grades_printer(student_current_data,
								(student_current_data->grade_student));
		}
	}
	return FAILURE;
}

int grades_print_all(struct grades *grades){
	if (!grades) {
		return FAILURE;
	}
	struct iterator *tmp_student = list_begin((grades->list_students));
	while(tmp_student){
		struct type_student *student_d = list_get(tmp_student);
		int id_tmp=(int)(student_d->id);
		if(!grades_print_student(grades, id_tmp)){
			tmp_student =list_next(tmp_student);
		}
		else {
			return FAILURE;
		}
	}
	return SUCCESS;
}
 /*prints the student,id,grade*/
static int grades_printer(struct type_student *type_student,
							struct list * grade_student){
	if (!type_student || !grade_student) {
		return FAILURE;
	}
	int id= type_student-> id;
	int course_num = type_student->course_num;
	printf("%s %d:",(type_student-> name), id);
	struct iterator *student_current_course=list_begin(grade_student);
	if(!(course_num)){
		printf("\n");
		return SUCCESS;
	}
	if(!student_current_course){
		return FAILURE;
	}
	for(int i=NEXT;i< course_num;i++){
		struct type_course * course_current_data =
					list_get(student_current_course);
		if(!course_current_data){
			return FAILURE;
		}
		else{
			int grade=(course_current_data->grade);
			printf("%s %d,", (course_current_data->name_of_course), grade);
			student_current_course =list_next(student_current_course);
		}
	}
	struct type_course *course_current_data =list_get(student_current_course);
	if(!course_current_data){
		return FAILURE;
	}
	else{
		int grade=(course_current_data->grade);
		printf("%s %d\n", (course_current_data->name_of_course), grade);
	}
	return SUCCESS;
}

struct grades* grades_init(){ 
    struct grades *new_grades;
	new_grades =(struct grades*)(malloc(sizeof(struct grades)));
	if (!new_grades) {
		free(new_grades);
		return SUCCESS;
	}
	new_grades->list_students = list_init(clone_student, destroy_student_data);
	return new_grades;
}

int clone_student(void* argu, void** out) {
	struct type_student* cloned_data;
	cloned_data = (struct type_student*)argu;
	struct type_student* out_tmp;
	char* name_tmp_new;
	name_tmp_new = (char*)malloc
					(sizeof(char*)*(strlen(cloned_data->name) + NEXT));
	out_tmp = (struct type_student*)(malloc(sizeof(struct type_student)));
	if (!out_tmp || !name_tmp_new) {
		free(name_tmp_new);
		free(out_tmp);
		return FAILURE;
	}
	else {
		strcpy(name_tmp_new, cloned_data->name);
		out_tmp->id = cloned_data->id;
		out_tmp->course_num = cloned_data->course_num;
		out_tmp->average = cloned_data->average;
		out_tmp->grade_student = list_init(clone_course, destroy_course_data);
		out_tmp->name = name_tmp_new;
		*out = out_tmp;
	}
	return SUCCESS;
}

void destroy_student_data(void* argu) {
	struct type_student* desroyed_data = (struct type_student*)argu;
	free((desroyed_data->name));
	/*free the course list*/
	list_destroy((desroyed_data->grade_student));
	free(argu);
}

int clone_course(void* argu, void** out) {
	struct type_course* cloned_data = (struct type_course*)argu;
	struct type_course* out_tmp;
	char* name_tmp_new;
	name_tmp_new = (char*)malloc
			(sizeof(char*)*(strlen(cloned_data->name_of_course) + NEXT));
	out_tmp = (struct type_course*)malloc(sizeof(struct type_course));
	if (!out_tmp || !name_tmp_new) {
		free(name_tmp_new);
		free(out_tmp);
		return FAILURE;
	}
	else {
		strcpy(name_tmp_new, cloned_data->name_of_course);
		out_tmp->grade = cloned_data->grade;
		out_tmp->name_of_course = name_tmp_new;
		*out = out_tmp;
	}
	return SUCCESS;
}


void  destroy_course_data (void *argu){
	struct type_course *desroyed_data =(struct type_course*)argu;
	free((desroyed_data->name_of_course));
	free(argu);	
}


void grades_destroy(struct grades *grades){
	list_destroy((grades->list_students));
	free(grades);
}
