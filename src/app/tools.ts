export function copyArray(data) {
    return JSON.parse(JSON.stringify(data));
}

export function indexTracker(index: number, value: any) {
    return index;
}
