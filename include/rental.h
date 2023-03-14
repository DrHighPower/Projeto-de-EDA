typedef struct userInformation User;
typedef struct transportInformation Transport;

int pay_rental(User** head_user, Transport* head_transport, int user_id, int transport_id, int min_used, int bool);
int store_rental(User** head_user, Transport* head_transport, int user_id, int transport_id, int bool);