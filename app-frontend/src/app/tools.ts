export function copyArray(data): any {
    return JSON.parse(JSON.stringify(data));
}

export function indexTracker(index: number, value: any): number {
    return index;
}
