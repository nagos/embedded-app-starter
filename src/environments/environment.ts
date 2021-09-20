import { DEV_IP } from '../../debug';

export const environment = {
    dev_ip: 'ws://' + DEV_IP + '/app',
    log_url: 'http://'+DEV_IP+'/log',
    production: false
};
