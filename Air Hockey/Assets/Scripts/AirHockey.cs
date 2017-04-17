using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AirHockey : MonoBehaviour {

	public Vector3 puckPosition;
	public Vector3 malletPosition;
	public Vector3 puckVelocity;
	public Vector3 malletVelocity;
	public GameObject puck;
	public GameObject mallet;
	void Awake(){
		if (puck == null)
			Debug.LogError ("Wtf is puck?");
		if (mallet == null)
			Debug.LogError ("Wtf is mallet?");
	}

	void Start(){
		puck.transform.position = puckPosition;
		mallet.transform.position = malletPosition;
		puck.GetComponent<Rigidbody2D> ().velocity = puckVelocity;
		mallet.GetComponent<Rigidbody2D> ().velocity = malletVelocity;
	}
	void Update(){
		puckVelocity = new Vector2(
			Mathf.Clamp (puck.GetComponent<Rigidbody2D> ().velocity.x, -500f, 500f),
			Mathf.Clamp (puck.GetComponent<Rigidbody2D> ().velocity.y, -500f, 500f)
		);
		malletVelocity = new Vector2(
			Mathf.Clamp (mallet.GetComponent<Rigidbody2D> ().velocity.x, -200f, 200f),
			Mathf.Clamp (mallet.GetComponent<Rigidbody2D> ().velocity.y, -200f, 200f)
		);
		puck.GetComponent<Rigidbody2D> ().velocity = puckVelocity;
		mallet.GetComponent<Rigidbody2D> ().velocity = malletVelocity;
		malletPosition = new Vector2(mallet.transform.position.x,Mathf.Clamp (mallet.transform.position.y, 0f, 500f));
		mallet.transform.position = malletPosition;
		Debug.Log (puck.GetComponent<Rigidbody2D> ().velocity + "and " + mallet.GetComponent<Rigidbody2D> ().velocity);
	}

}
