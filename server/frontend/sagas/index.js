import {authWatcher} from './auth';
import {fork} from 'redux-saga/effects'

export default function* root() {
	yield [
		fork(authWatcher),
	];
}