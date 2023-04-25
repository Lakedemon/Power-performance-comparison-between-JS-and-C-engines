import {Engine} from "./Engine.js";
import {PBRShader} from "../GL Helpers/ShaderHandler.js";
import {loadGLTF} from "../GL Helpers/AssetLoader.js";
import {FirstPersonController} from "./FirstPersonController.js";
import {SceneGraph} from "./SceneGraph.js";

window.onload = async function () {
    console.log(sessionStorage.getItem("pathToDemo"));
    let data = await loadGLTF(sessionStorage.getItem("pathToDemo") || "Scenario2");
    let scene = SceneGraph.fromGLTF(data, PBRShader);

    const nonEuclideanParadise = new Engine(PBRShader, scene, 1440);
    nonEuclideanParadise.start();

    let player = new FirstPersonController(nonEuclideanParadise.activeScene.mainCamera.transform, 0.015);
    window.addEventListener(nonEuclideanParadise.update.type, () => player.move());
}

canvas.onclick = function() {
    canvas.requestPointerLock();
    canvas.requestFullscreen().catch((err) => {
        alert(`Error attempting to enable fullscreen mode: ${err.message} (${err.name})`);
    });
};