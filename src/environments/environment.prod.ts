const loc = window.location;
export const environment = {
    dev_ip: 'ws://' + loc.host + '/app',
    log_url: 'http://'+loc.host+'/log',
    production: true
};
