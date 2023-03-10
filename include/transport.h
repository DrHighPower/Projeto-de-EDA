typedef struct transportInformation {
	int id, battery, autonomy;
	float price;
	char *type, *geocode;
	struct transportInformation* next;
} Transport;

void free_transport_list(Transport* head);
int store_transports(Transport* head, int bool);
int read_transports(Transport* head, int bool);