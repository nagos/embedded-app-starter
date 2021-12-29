#ifndef PROFITT_SECURITY_H
#define PROFITT_SECURITY_H

#ifdef __cplusplus
extern "C" {
#endif

enum {PROFITT_DI_DISABLE, PROFITT_DI_ENABLE};

void secutiry_set_password(const char * password);
void secutiry_set_profitt_di(int profitt_di);

#ifdef __cplusplus
}
#endif

#endif
