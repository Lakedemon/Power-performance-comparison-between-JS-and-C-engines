import {SceneGraph} from "./SceneGraph.js";

export class Engine {
    #timer = 0;
    #startTime;
    activeScene;

    constructor(mainShader, scene) {
        window.gl = canvas.getContext("webgl2", {stencil:true});
        gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);

        this.activeScene = scene ?? new SceneGraph(mainShader);
        this.update = new Event("update");
        this.#startTime = Date.now();
    }

    start() {
        this.#renderLoop();
    }

    #renderLoop() {
        this.#resizeCanvas();

        this.#updateTime();
        this.activeScene.animate(this.#timer / 1000);
        this.activeScene.updateScene();
        this.activeScene.portalDraw();

        window.requestAnimationFrame(this.#renderLoop.bind(this));
        window.dispatchEvent(this.update);
    }

    #resizeCanvas() {
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
        gl.viewport(0, 0, canvas.width, canvas.height);
        this.activeScene.mainCamera.resetProjection();
    }

    #updateTime() {
        this.#timer = Date.now() - this.#startTime;
    }
}

