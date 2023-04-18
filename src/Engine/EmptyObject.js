import {Transform} from "./Transform.js";

export class EmptyObject {
    transform;

    constructor() {
        this.transform = new Transform();
    }

    get worldMatrix(){
        return this.transform.worldMatrix;
    }

    setPosition(v) {
        this.transform.position = v;
    }

    setRotation(v) {
        this.transform.rotation = v;
    }

    setScale(v) {
        this.transform.scale = v;
    }
}