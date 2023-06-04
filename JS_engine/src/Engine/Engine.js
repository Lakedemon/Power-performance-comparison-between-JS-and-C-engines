import {SceneGraph} from "./SceneGraph.js";

export class Engine {
    #timer = 0;
    #startTime;
    activeScene;
    #framesElapsed = 0;

    constructor(mainShader, scene, runForNFrames = 0) {
        window.gl = canvas.getContext("webgl2", {stencil:true});
        gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);

        this.activeScene = scene ?? new SceneGraph(mainShader);
        this.update = new Event("update");
        this.#startTime = Date.now();
        this.runForNFrames = runForNFrames;
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

        this.#updateFrameCount();
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

    #updateFrameCount(){
        this.#framesElapsed += 1;
        console.log(this.#framesElapsed);
        if(this.#framesElapsed >= this.runForNFrames && this.runForNFrames !== 0){
            this.#shutdownServer();
        }
    }

     #shutdownServer() {
        fetch('http://localhost:8000/shutdown')
            .then(response => {
                if (response.ok) {
                    console.log('Server shutdown successful.');
                    window.close();
                } else {
                    console.error('Server shutdown failed.');
                }
            })
            .catch(error => {
                console.error('Error sending shutdown request:', error);
            });
    }
}

