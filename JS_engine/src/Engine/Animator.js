import {glMath, Vector3, Vector4} from "../Math/index.js";

export class Animator{
    channels;

    constructor(channels){
        this.channels = channels;
    }

    animate(t){
        this.channels.forEach(channel =>{
            channel.updateNode(t);
        })
    }
}

export class Channel{
    static paths = Object.freeze({
        translation     : (node, v) => node.setPosition(v),
        rotation        : (node, v) => node.setRotation(v),
        scale           : (node, v) => node.setScale(v)
    });

    node;
    path;
    sampler;

    constructor(node, path, sampler){
        this.node = node;
        this.path = path;
        this.sampler = sampler;
    }

    updateNode(t){
        this.path(this.node, this.sampler.getOutput(t));
    }
}

export class Sampler{
    static interpolationModes = Object.freeze({
        LINEAR          : (start, end, t) => Sampler.lerp(start, end, t),
        STEP            : (start, end, t) => Sampler.stepInterp(start, end, t),
        CATMULLROMSPLINE: (start, end, t) => null,
        CUBICSPLINE     : (start, end, t) => null,
        rotation        : (start, end, t) => Sampler.slerp(start, end, t),
    });

    input;
    output;
    mode;
    elementSize;

    constructor(input, output, elementSize, mode = Sampler.interpolationModes.LINEAR){
        this.input = input;
        this.output = output;
        this.mode = mode;
        this.elementSize = elementSize;

        this.duration = input[input.length - 1] - input[0];
        this.frameLength = this.duration / input.length;

        this.input[0] = 0;
    }

    getOutput(globalT){
        let localT = globalT % this.duration;
        let index = Math.min(Math.floor(localT / this.frameLength), this.input.length - 1);

        while (!(this.input[index] <= localT && this.input[index + 1] >= localT)){
            if(this.input[index] <= localT){
                index += 1;
            } else {
                index -= 1;
            }
            if(index >= this.input.length - 1){
                index = 0;
            }
        }
        let t = (localT - this.input[index]) / (this.input[index + 1] - this.input[index]);

        return this.mode(
            new (this.elementSize === 3 ? Vector3 : Vector4)(...this.output.slice(index * this.elementSize, (index + 1) * this.elementSize)),
            new (this.elementSize === 3 ? Vector3 : Vector4)(...this.output.slice((index + 1) * this.elementSize, (index + 2) * this.elementSize)),
            t
        );
    }

    static lerp(start, end, t) {
        return start.scale(1 - t).add(end.scale(t));
    }

    static stepInterp(start, end, t) {
        return start;
    }

    static slerp(start, end, t){
        let dot = Vector4.dot(start, end);

        if (dot >= 0.9995){
            return Vector3.QuaternionToEuler(...Sampler.lerp(start, end, t).normalized);
        }

        let s = Math.sign(dot);
        let a = Math.acos(Math.abs(dot));

        if(a <= glMath.EPSILON){
            return Vector3.QuaternionToEuler(...Sampler.lerp(start, end, t).normalized);
        }

        let r_sa = 1 / Math.sin(a);
        let vt = start.scale(Math.sin(a * (1 - t)) * r_sa).add(end.scale(s * (Math.sin(a * t) * r_sa)))
        return Vector3.QuaternionToEuler(...vt);
    }
}