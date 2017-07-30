import {authWatcher} from './auth';
import {fork, put} from 'redux-saga/effects';
import {checkAuth} from '../actions/auth';

export default function* root() {
	yield [
		fork(authWatcher),
	];
	yield put(checkAuth());
}
