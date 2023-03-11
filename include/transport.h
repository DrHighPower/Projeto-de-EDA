typedef struct transportInformation {
	int id, battery, autonomy;
	float price;
	char *type, *geocode;
	struct transportInformation* next;
} Transport;

void free_transport_list(Transport** head);
int store_transports(Transport* head, int bool);
void save_transport(Transport* current, int id, int battery, int autonomy, float price, char* type, char* geocode);
Transport* read_transports(Transport* head, int bool);
void insert_tranport(Transport** head);